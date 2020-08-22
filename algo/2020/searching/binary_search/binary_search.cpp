#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename iterator_type, typename value_type>
auto binary_search_iterative(iterator_type p, iterator_type r, value_type v)
{
    auto e = r;
    auto d = distance(p,r);
    auto m = p + d/2;
    while (d > 0) {
        if (v == *m) return m;
        else if (v < *m) r = m;
        else if (v > *m) p = next(m);
        d = distance(p,r);
        m = p + d/2;
    }
    return e;
}


template <typename iterator_type, typename value_type>
auto binary_search_recursive(iterator_type p, iterator_type r, value_type v)
{
    static const auto e = r;
    auto d = distance(p,r);
    auto m = p + d/2;
    if (d <= 0) return e;
    else if (v < *m) return binary_search_recursive(p,m,v);
    else if (v > *m) return binary_search_recursive(next(m),r,v);
    else return m;
}

int main()
{
    vector<int> v {3,1,4,1,5,9};
    sort(begin(v),end(v));
    auto i = binary_search_iterative(begin(v),end(v),1);
    if (i != end(v)) {
        cout << (*i) << endl;
    }
    auto j = binary_search_iterative(begin(v),end(v),2);
    if (j != end(v)) {
        cout << (*j) << endl;
    }
}

