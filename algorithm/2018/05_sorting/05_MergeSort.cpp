#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

template <typename ForwardIterator>
void merge_sort(ForwardIterator p, ForwardIterator r)
{
    if (distance(p,r) <= 1) return;
    auto m = p + distance(p,r)/2;
    merge_sort(p, m);
    merge_sort(m, r);
    inplace_merge(p, m, r);
}

#ifndef NENTRY
int main()
{
    vector<int> v = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9};
    merge_sort(begin(v), end(v));
    assert(is_sorted(begin(v), end(v)));
}
#endif

