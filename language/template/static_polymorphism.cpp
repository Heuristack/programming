#include <iostream>
using namespace std;

template <typename derived>
struct base
{
    void interface()
    {
        static_cast<derived*>(this)->implementation();
    }
};

struct derived : base<derived>
{
    void implementation()
    {
        cout << "Hello, static polymorphsim!" << endl;
    }
};

int main()
{
    derived d;
    d.interface();
}

