#include <blpapi_correlationid.h>
#include <blpapi_session.h>
#include <exception>
#include <iostream>

namespace BippeClient
{
using namespace BloombergLP::blpapi;

SessionOptions get_session_options(std::string const & IP, std::string const & application_name)
{
    SessionOptions SO;
    SO.setServerHost(IP.data());
    SO.setServerPort(8194);
    std::string AO = "AuthenticationMode=APPLICATION_ONLY;ApplicationAuthenticationType=APPNAME_AND_KEY;ApplicationName=";
    AO.append(application_name);
    SO.setAuthenticationOptions(AO.data());
    return SO;
}

template <typename F>
void for_each_message(Event const & event, F func, bool print = false)
{
    MessageIterator MI(event);
    while (MI.next()) {
        Message M = MI.message();
        if (print) {
            M.print(std::cout);
        }
        func(M);
    }
}

class EventPrinter {
public:
    EventPrinter(Event const & event): e(event) {}
    std::ostream & puts(std::ostream & s)
    {
        for_each_message(e, [&s](Message const & m){
            m.print(s);
        });
        return s;
    }
private:
    Event const & e;
};
std::ostream & operator<<(std::ostream & s, Event const & e)
{
    return EventPrinter(e).puts(s);
}

class CorrelationIdGenerator {
public:
    static CorrelationId generate()
    {
        return CorrelationId(++correlation_identifier);
    }

private:
    static unsigned int correlation_identifier;
};
unsigned int CorrelationIdGenerator::correlation_identifier = 0;

class TokenGenerator {
public:
    static std::string generate(Session & session, CorrelationId corrid = CorrelationIdGenerator::generate())
    {
        std::string T;
        EventQueue Q;
        session.generateToken(corrid, &Q);
        for_each_message(Q.nextEvent(), [&T](Message const & m){
            if ("TokenGenerationSuccess" == m.messageType()) {
                T = m.getElementAsString("token");
            }
        });
        last_generated_token = T;
        return T;
    }
    static std::string get_last_generated_token()
    {
        return last_generated_token;
    }
private:
    static std::string last_generated_token;
};
std::string TokenGenerator::last_generated_token = "";

class SessionAuthorizer {
public:
    static bool authorize(Session & session)
    {
        bool success = false;
        if (!session.openService("//blp/apiauth")) {
            return false;
        }
        Request REQ = session.getService("//blp/apiauth").createAuthorizationRequest();
        REQ.set("token", TokenGenerator::generate(session).data());
        Identity ID = session.createIdentity();
        EventQueue Q;
        session.sendAuthorizationRequest(REQ, &ID, CorrelationIdGenerator::generate(), &Q);

        for_each_message(Q.nextEvent(),[&success](Message const & m){
            if ("AuthorizationSuccess" == m.messageType()) {
                success = true;
            }
        });
        identity = ID;
        return success;
    }
    static Identity const & get_identity() { return identity; }
private:
    static Identity identity;
};
Identity SessionAuthorizer::identity;

class EventLoop {
public:
    EventLoop(Session & s): session(s) {}
    [[noreturn]] void run()
    {
        while (true) {
            for_each_message(session.nextEvent(),[](Message const & m){}, true);
        }
    }
    Session & session;
private:
};

class MarketDataSubscriber {
public:
    MarketDataSubscriber(Session & s, std::string const & n): session(s), service_name(n)
    {
        if (!service_name.empty() && session.openService(service_name.data())) {
            service_open = true;
        }
    }

    enum class SubscriptionLevel { list, data, book };
    MarketDataSubscriber(Session & s, SubscriptionLevel level = SubscriptionLevel::data): session(s) {
        switch(level) {
            case SubscriptionLevel::list:
                service_name = "//blp/mktlist";
                break;
            case SubscriptionLevel::book:
                service_name = "//blp/mktdepth";
                break;
            case SubscriptionLevel::data:
                service_name = "//blp/mktdata";
                break;
        }
        if (session.openService(service_name.data())) {
            service_open = true;
        }
    }

    void subscribe(std::string const & description)
    {
        if (!service_open) {
            std::cerr << "Service is not open" << std::endl;
            return;
        }
        SubscriptionList subscriptionlist;
        subscriptionlist.add(description.data(), CorrelationIdGenerator::generate());
        session.subscribe(subscriptionlist, SessionAuthorizer::get_identity());
    }

    void subscribe(std::string const & securities, std::string const & fields)
    {
        if (!service_open) {
            std::cerr << "Service is not open" << std::endl;
            return;
        }
        SubscriptionList subscriptionlist;
        subscriptionlist.add(securities.data(), fields.data(), "", CorrelationIdGenerator::generate());
        session.subscribe(subscriptionlist, SessionAuthorizer::get_identity());
    }

private:
    Session & session;
    std::string service_name;
    bool service_open = false;
};

}

int main(int argc, char ** argv)
try {
    using namespace BloombergLP::blpapi;
    using namespace BippeClient;

    if (argc != 3) {
        std::cerr << "Invalid argument: BpipeClient <IP> <ApplicationName>";
        return -1;
    }

    Session session(get_session_options(argv[1], argv[2]));
    if (!session.start()) {
        std::cerr << "Failed to start session" << std::endl;
        return -1;
    }
    std::cout << "Session is authenticated" << std::endl;

    if (!SessionAuthorizer::authorize(session)) {
        std::cerr << "Failed to authorize session" << std::endl;
        return -1;
    }
    std::cout << "Session is authorized" << std::endl;

//  MarketDataSubscriber list_subscriber(session, MarketDataSubscriber::SubscriptionLevel::list);
//  list_subscriber.subscribe("//blp/mktlist/chain/eid/39544");

//  MarketDataSubscriber market_depth_subscriber(session, MarketDataSubscriber::SubscriptionLevel::book);
//  market_depth_subscriber.subscribe("1288 HK Equity", "BEST_BID1, BEST_ASK1");

    MarketDataSubscriber list_subscriber(session, MarketDataSubscriber::SubscriptionLevel::list);
    list_subscriber.subscribe("//blp/mktdata/bbgid/BBG000JB5HR2");

    MarketDataSubscriber market_data_subscriber(session);
    market_data_subscriber.subscribe("//blp/mktdata/bbgid/BBG000JB5HR2",
        "BEST_BID, BEST_ASK, "
        "LAST_PRICE, SIZE_LAST_TRADE, LAST_DIR, TRADE_UPDATE_STAMP_RT, "
        "MKTDATA_EVENT_TYPE, MKTDATA_EVENT_SUBTYPE, "
        "EVT_TRADE_IDENTIFIER_RT, EVT_TRADE_INTEGER_IDENTIFIER_RT, "
        "LAST_ASK_TIME_TODAY_REALTIME, LAST_BID_TIME_TODAY_REALTIME, LAST_PRICE_TIME_TODAY_REALTIME, LAST_TRADE_PRICE_TIME_TODAY_RT, "
        "THEORETICAL_TIME_TODAY_RT, "
        "EVT_QUOTE_ASK_DETERMINED_TIME_RT, EVT_QUOTE_ASK_TIME_RT, EVT_QUOTE_BID_DETERMINED_TIME_RT, EVT_QUOTE_BID_TIME_RT, "
        "EVT_TRADE_CANCEL_TIME_RT, EVT_TRADE_CORRECT_TIME_RT, EVT_TRADE_EXECUTION_TIME_RT, EVT_TRADE_TIME_RT");

    EventLoop loop(session);
    loop.run();

    session.stop();
}
catch (const BloombergLP::blpapi::Exception & e) {
    std::cerr << "Bloomberg library exception caught: " << e.what() << std::endl;
}
catch (const std::exception & e) {
    std::cerr << "Standard library exception caught: " << e.what() << std::endl;
}
catch (...) {
    std::cerr << "Uknown exception caught" << std::endl;
}
