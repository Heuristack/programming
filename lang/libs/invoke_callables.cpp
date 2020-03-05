#include <iostream>
#include <functional>
#include <string>

using namespace std;

class object
{
public:
    object(string const & s) : member(s) {}
    auto print() const  { cout << member << endl; }
    auto operator()() const { print(); }
    string member;
};

int main()
{
    string const s = "Hello, Invoke!";
    object const o(s);

    // 1. invoke a function
    invoke(printf,"%s\n",s.data());

    // 2. invoke a lambda
    invoke([](auto const & s){ cout << s << endl; }, s);

    // 3. invoke a functor (function object)
    invoke(o);

    // 4. invoke a member function
    invoke(&object::print,o);

    // 5. invoke (access) a data member
    cout << invoke(&object::member,object(s)) << endl;
}

