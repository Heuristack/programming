#include <iostream>
#include <type_traits>
using namespace std;

template <unsigned I, typename ... Ts>
struct select;

template <unsigned I, typename T, typename ... Ts>
struct select<I,T,Ts...> : select<I-1,Ts...> {};

template <typename T, typename ... Ts>
struct select<0,T,Ts...> { using type = T; };

int main()
{
    select<1,int,double,string>::type value;
    static_assert(is_same_v<decltype(value),double>);
}

