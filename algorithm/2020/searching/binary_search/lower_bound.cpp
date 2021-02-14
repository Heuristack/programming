#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

template <typename iterator_type, typename value_type>
auto lower_bound_search(iterator_type p, iterator_type r, value_type v)
{
    auto e = r;
    auto d = distance(p,r);
    while (d > 0) {
        if (auto m = p + d/2; v <= *m) { e = r = m; }
        else { p = next(m); }
        d = distance(p,r);
    }
    return e;
}

int main()
{
    vector<int> v {-14,-10,2,108,108,243,285,285,285,401};
    assert(lower_bound_search(begin(v),end(v),-20) == lower_bound(begin(v),end(v),-20));
    assert(lower_bound_search(begin(v),end(v),285) == lower_bound(begin(v),end(v),285));
    assert(lower_bound_search(begin(v),end(v),250) == lower_bound(begin(v),end(v),250));
    assert(lower_bound_search(begin(v),end(v),402) == lower_bound(begin(v),end(v),402));
}

