#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

template<typename ForwardIterator>
void insertion_sort(ForwardIterator p, ForwardIterator r)
{
    for (auto i = p; i != r; i++) {
        rotate(upper_bound(p,i,*i),i,next(i));
    }
}

#ifndef NENTRY
int main()
{
    vector<int> v = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9};
    insertion_sort(begin(v), end(v));
    assert(is_sorted(begin(v), end(v)));
}
#endif

