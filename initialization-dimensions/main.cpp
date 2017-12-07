#include <iostream>

using std::cout;
using std::endl;

int main()
{
struct T
{
    int m, n;

   ~T()
    {
        cout << "D0" << endl;
    }

#ifdef EC0
    explicit
#endif
    T()
    : m(0), n(0)
    {
        cout << "C0" << endl;
    }

#ifdef EC1
    explicit
#endif
    T(int a)
    : m(a), n(0)
    {
        cout << "C1" << endl;
    }

#ifdef EC2
    explicit
#endif
    T(int a, int b)
    : m(a), n(b)
    {
        cout << "C2" << endl;
    }

#ifdef ECP
    explicit
#endif
    T(const T & t)
    : m(t.m), n(t.n)
    {
        cout << "CP" << endl;
    }
};

T s;

#ifdef NL0
{
    T o;
    T u =;
}
#endif
#ifdef RL0
{
    T o();
    T u = ();
}
#endif
#ifdef CL0
{
    T o{};
    T u = {};
}
#endif

#ifdef NL1
{
    T o 1;
    T u = 1;
}
#endif
#ifdef RL1
{
    T o(1);
    T u = (1);
}
#endif
#ifdef CL1
{
    T o{1};
    T u = {1};
}
#endif

#ifdef NL2
{
    T o 2,2;
    T u = 2,2;
}
#endif
#ifdef RL2
{
    T o(2,2);
    T u = (2,2);
}
#endif
#ifdef CL2
{
    T o{2,2};
    T u = {2,2};
}
#endif

#ifdef NLP
{
    T o s;
    T u = s;
}
#endif
#ifdef RLP
{
    T o(s);
    T u = (s);
}
#endif
#ifdef CLP
{
    T o{s};
    T u = {s};
}
#endif

}

