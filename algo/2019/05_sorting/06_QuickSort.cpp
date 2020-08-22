#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

template <typename ForwardIterator>
void quick_sort(ForwardIterator p, ForwardIterator r)
{
    if (distance(p,r) <= 0) return;
    auto m = *(p + distance(p,r)/2);
    auto u = partition(p, r, [m](auto const & e){ return e <= m; });
    auto l = partition(p, u, [m](auto const & e){ return e <  m; });
    quick_sort(p, l);
    quick_sort(u, r);
}

#ifndef NENTRY
int main()
{
    vector<int> v = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9};
    quick_sort(begin(v), end(v));
    assert(is_sorted(begin(v), end(v)));
}
#endif

