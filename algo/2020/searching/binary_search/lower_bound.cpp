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
    auto m = p + d/2;
    while (d > 0) {
        if (v == *m) { e = m; r = m; }
        else if (v < *m) { r = m; }
        else { p = next(m); }
        d = distance(p,r);
        m = p + d/2;
    }
    return e;
}

int main()
{
    vector<int> v {-14,-10,2,108,108,243,285,285,285,401};
    assert(lower_bound_search(begin(v),end(v),285) == lower_bound(begin(v),end(v),285));
    // todo : fix me
    cout << *(lower_bound_search(begin(v),end(v),250)) << endl;
    cout << *(lower_bound(begin(v),end(v),250)) << endl;
}

