#include "dbg/dbg.h"

using namespace std;

template <typename string_t>
class string_wrapper
{
public:
    typedef string_t string_type;
    typedef string_wrapper<string_type> this_type;

public:
    string_wrapper(string_type const & s) : m(s) {}
    string_wrapper() = default;

private:
    string_type m = "Null";

public:
    friend ostream & operator<<(ostream & s, this_type const & o)
    {
        return s << o.m;
    }
};

int main()
{
    long long integer = 0xFF;
    string message {"Hello,World!"};
    string_wrapper<string> wrapper(message);
    dbg(integer);
    dbg(message);
    dbg(wrapper);
}

