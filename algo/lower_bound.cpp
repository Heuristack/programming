#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

template <typename iterator, typename value>
auto lower_bound_search(iterator b, iterator e, value v)
{
    auto r = e;
    auto d = distance(b,e);
    auto m = b + d/2;
    while (d > 0) {
        if (v == *m) { r = m; e = m; }
        else if (v < *m) { e = m; }
        else { b = next(m); }
        d = distance(b,e);
        m = b + d/2;
    }
    return r;
}

int main()
{
    vector<int> v {-14,-10,2,108,108,243,285,285,285,401};
    assert(lower_bound_search(begin(v),end(v),285) == lower_bound(begin(v),end(v),285));
}

