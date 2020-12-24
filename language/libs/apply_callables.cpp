#include <functional>
#include <algorithm>
#include <array>
#include <iostream>

using namespace std;

template <typename comparable = long>
auto bigger(comparable a, comparable b)
{
    return std::max(a,b);
}

int main()
{
    auto t = make_tuple(1,2);
    cout << apply(bigger<int>,t) << endl;

    array<int,2> a {1,2};
    cout << apply(bigger<int>,a) << endl;
}

