#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template<typename I, typename F>
auto partition_forward(I b, I e, F p) -> I
{
    auto n = b;
    for (auto i = b; i != e; i++) {
        if (p(*i)) {
            iter_swap(n++, i);
        }
    }
    return n;
}

int main()
{
    vector<int> v = {6,7,8,1,2,3};
    partition_forward(begin(v), end(v), [](auto const & e){ return e < 5; });
    for (auto const & e : v) { cout << e << endl; }
}

