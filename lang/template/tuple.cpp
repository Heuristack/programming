#include <iostream>
#include <string>
using namespace std;

/**
 * Recursion => Contain-Relation
 *
 * list => list,value
 *      => epsilon
 *
 * T2{T1{T0{value},value},value}
 *
 * Subobject contain-relation can be used to imitate recursion
 *
**/
struct T0 { int value; };
struct T1 : T0 { double value; };
struct T2 : T1 { string value; };
auto get0(T2 const & T) { return T.T0::value; }
auto get1(T2 const & T) { return T.T1::value; }
auto get2(T2 const & T) { return T.T2::value; }

/**
 * Subobject contain-relation can be implemented by class template
 *
 * Tuple<int>
 * Tuple<int,double> : Tuple<int>
 * Tuple<int,double,string> : Tuple<int,double>
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
auto get(Tuple<T,Ts...> const & t)
{
    return Value<i,T,Ts...>::value(&t);
}

int main()
{
    T2 object {1,2.3,"4"};
    cout << get0(object) << get1(object) << get2(object) << endl;

    Tuple<int,double,string> t{1,2.3,"4"};
    cout << get<0>(t) << get<1>(t) << get<2>(t) << endl;
}

