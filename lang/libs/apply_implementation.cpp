#include <functional>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename comparable = long>
auto bigger(comparable a, comparable b)
{
    return std::max(a,b);
}

template <int ...> struct seq {};
template <int n, int ...s> struct gen : gen<n-1,n-1,s...> {};
template <int ...s> struct gen<0,s...> { typedef seq<s...> type; };

template <typename callable, int ...s, typename ...params>
auto apply0(callable function, tuple<params...> packed_params, seq<s...>)
{
    return function(get<s>(packed_params)...);
}

template <typename callable, typename ...params>
auto apply1(callable function, tuple<params...> packed_params)
{
    return apply0(function, packed_params, typename gen<sizeof ...(params)>::type());
}

int main()
{
    auto t = make_tuple(1,2);
    cout << apply1(bigger<int>,t) << endl;
}

