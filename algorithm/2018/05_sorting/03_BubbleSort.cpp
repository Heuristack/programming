#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

template <typename BidirectionalIterator>
void bubble_sort(BidirectionalIterator p, BidirectionalIterator r)
{
    for (auto j = r; j != p; j--) {
        for (auto i = p; next(i) != j; i++) {
            if (*i > *next(i)) {
                iter_swap(i, next(i));
            }
        }
    }
}

#ifndef NENTRY
int main()
{
    vector<int> v = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9};
    bubble_sort(begin(v), end(v));
    assert(is_sorted(begin(v), end(v)));
}
#endif

