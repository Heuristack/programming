#include <iostream>
#include <string>
using namespace std;

/**
 * Recursion => Contain-Relation
 *
 * list := value,list
 *      := epsilon
 *
 * list := {value,{value,{value,{}}}}
 *
**/

/**
 * Subobject contain-relation can be used to imitate recursion
 *
 * T0{value,T1{value,T2{value}}}
 *
**/
struct T2 { T2(string const & s): value{s} {} string value; };
struct T1 : T2 { T1(double d, string const & s): T2{s}, value{d} {} double value; };
struct T0 : T1 { T0(int v, double d, string const & s): T1{d,s}, value{v} {}  int value; };
auto get0(T0 const & T) { return T.T0::value; }
auto get1(T0 const & T) { return T.T1::value; }
auto get2(T0 const & T) { return T.T2::value; }

/**
 * Subobject contain-relation can be implemented by class template hierarchy
 *
 * Tuple<string> { string value; }
 * Tuple<double,string> : Tuple<string> { double value; }
 * Tuple<int,double,string> : Tuple<double,string> { int value; }
 *
**/
template <typename T, typename ... Ts>
struct Tuple : Tuple<Ts...>
{
    Tuple(T v, Ts ... vs): Tuple<Ts...>{vs...}, value{v} {}
    T value;
};

template <typename T>
struct Tuple<T>
{
    Tuple(T v): value{v} {}
    T value;
};

template <int i, typename T, typename ... Ts>
struct Value
{
    static auto value(Tuple<T,Ts...> const * t)
    {
        return Value<i-1,Ts...>::value(t);
    }
};

template <typename T, typename ... Ts>
struct Value<0,T,Ts...>
{
    static auto value(Tuple<T,Ts...> const * t)
    {
        return t->value;
    }
};

template <int i, typename T, typename ... Ts>
auto Get(Tuple<T,Ts...> const & t)
{
    return Value<i,T,Ts...>::value(&t);
}

template <int i, typename T, typename ... Ts>
auto get(Tuple<T,Ts...> const & t)
{
    if constexpr (i == 0) { return t.value; }
    else { return get<i-1,Ts...>(t); }
}

int main()
{
    T0 object {1,2.3,"4"};
    cout << get0(object) << get1(object) << get2(object) << endl;

    Tuple<int,double,string> t{1,2.3,"4"};
    cout << get<0>(t) << get<1>(t) << get<2>(t) << endl;
}

