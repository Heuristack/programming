#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

template <unsigned i, typename T, typename ... Ts>
struct select
{
    using type = typename select<i-1,Ts...>::type;
};

template <typename T, typename ... Ts>
struct select<0,T,Ts...>
{
    using type = T;
};

int main()
{
    static_assert(is_same<select<1, double, int, string>::type, int>::value);
}

