Abstract Factory
----------------
Builder
-------
Factory Method
--------------
Prototype
---------
Singleton
---------
```C++
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Singleton
{
public:

    static Singleton * get_instance()
    {
        static Singleton * instance_ptr = nullptr;
        if (instance_ptr == nullptr) {
            instance_ptr = new Singleton();
        }
        return instance_ptr;
    }

private:
    Singleton() {}
};

int main()
{
    Singleton * instance_ptr1 = Singleton::get_instance();
    Singleton * instance_ptr2 = Singleton::get_instance();
    if (instance_ptr1 == instance_ptr2) {
        print_message("Singleton", "instantiated only once");
    }
}

```

Adapter
-------
Bridge
------
Composite
---------
Decorator
---------
Facade
------
Flyweight
---------
Proxy
-----

Chain of Responsibility
-----------------------
```C++
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Handler
{
public:
    Handler() {}
    Handler(Handler * successor): successor{successor} {}

public:
    virtual auto handle_request() -> void
    {
        if (successor != nullptr) {
            successor->handle_request();
        }
    }

    virtual auto can_handle() -> bool
    {
        return 0;
    }

private:
    Handler * successor = nullptr;
};

class Receiver1 : public Handler
{
public:
    Receiver1(): Handler{} {}
    Receiver1(Handler * successor): Handler{successor} {}

public:
    auto handle_request() -> void override
    {
        if (can_handle()) {
            print_message("Receiver1", "Handling the request ... ");
        }
        else {
            print_message("Receiver1", "Passing the request along the chain ... ");
            Handler::handle_request();
        }
    }

    auto can_handle() -> bool override
    {
        return 0;
    }
};

class Receiver2 : public Handler
{
public:
    Receiver2(): Handler{} {}
    Receiver2(Handler * successor): Handler{successor} {}

public:
    auto handle_request() -> void override
    {
        if (can_handle()) {
            print_message("Receiver2", "Handling the request ... ");
        }
        else {
            print_message("Receiver2", "Passing the request along the chain ... ");
            Handler::handle_request();
        }
    }

    auto can_handle() -> bool override
    {
        return 0;
    }
};

class Receiver3 : public Handler
{
public:
    Receiver3(): Handler{} {}
    Receiver3(Handler * successor): Handler{successor} {}

public:
    auto handle_request() -> void override
    {
        if (can_handle()) {
            print_message("Receiver3", "Handling the request ... ");
        }
        else {
            print_message("Receiver3", "Passing the request along the chain ... ");
            Handler::handle_request();
        }
    }

    auto can_handle() -> bool override
    {
        return 1;
    }
};

class Sender
{
public:
    static void main()
    {
        Handler * handler = new Handler{new Receiver1{new Receiver2{new Receiver3{}}}};
        print_message("Sender", "Issuing a request to a handler object ... ");
        handler->handle_request();
        delete handler;
    }
};

int main()
{
    Sender::main();
}

```
Command
-------
```C++
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Receiver1
{
public:
    void action1()
    {
        print_message("Receiver1", "Hello World!");
    }
};

class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

class Command1 : public Command
{
public:
    void execute() override
    {
        print_message("Command1", "Performing (carrying out) the request ... ");
        receiver1_ptr->action1();
    }

public:
    explicit Command1(Receiver1 * receiver1_ptr): receiver1_ptr{receiver1_ptr} {}
    ~Command1() override { delete receiver1_ptr; }

private:
    Receiver1 * receiver1_ptr = nullptr;
};

class Invoker
{
public:
    void operation()
    {
        print_message("Invoker", "Calling 'execute' on the installed command ... ");
        command_ptr->execute();
    }

public:
    explicit Invoker(Command * command_ptr): command_ptr{command_ptr} {}
    ~Invoker() { delete command_ptr; }

private:
    Command * command_ptr = nullptr;
};

int main()
{
    Invoker invoker {new Command1{new Receiver1{}}};
    invoker.operation();
}

```

Interpreter
-----------
```C++
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Context
{};

class AbstractExpression
{
public:
    AbstractExpression(string const & name): name{name} {}
    virtual ~AbstractExpression() = default;

public:
    virtual void interpret(Context const & context) = 0;
    virtual void add(AbstractExpression * expression) {}
    string const & get_name() const { return name; }

private:
    string name;
};

class NonTerminalExpression : public AbstractExpression
{
public:
   ~NonTerminalExpression() { for (auto expression : expressions)  delete expression;  }
    NonTerminalExpression(string const & name): AbstractExpression{name} {}

public:
    void interpret(Context const & context) override
    {
        print_message(get_name(), "");
        for (auto expression : expressions) {
            print_message("", "interpreting ... " + expression->get_name());
            expression->interpret(context);
        }
        print_message(get_name(), "finished");
    }

    void add(AbstractExpression * expression) override
    {
        expressions.push_back(expression);
    }

private:
    vector<AbstractExpression *> expressions;
};

class TerminalExpression : public AbstractExpression
{
public:
    TerminalExpression(string const & name): AbstractExpression{name} {}
public:
    void interpret(Context const & context) override
    {}
};

class Client
{
public:
    static void main()
    {
        AbstractExpression * nt_expr2 = new NonTerminalExpression("ntExpr2");
        nt_expr2->add(new TerminalExpression(" tExpr3"));
        nt_expr2->add(new TerminalExpression(" tExpr4"));
        nt_expr2->add(new TerminalExpression(" tExpr5"));
        AbstractExpression * nt_expr1 = new NonTerminalExpression("ntExpr1");
        nt_expr1->add(new TerminalExpression(" tExpr1"));
        nt_expr1->add(nt_expr2);
        nt_expr1->add(new TerminalExpression(" tExpr2"));
        Context context;
        nt_expr1->interpret(context);
        delete nt_expr1;
    }
};

int main()
{
    Client::main();
}

```

Iterator
--------
Mediator
--------
Memento
-------
Observer
--------
State
-----
Strategy
--------
Template Method
---------------
Visitor
-------

