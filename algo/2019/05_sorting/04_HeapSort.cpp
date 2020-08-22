#include <algorithm>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

template <typename RandomAccessIterator>
void heap_sort(RandomAccessIterator p, RandomAccessIterator r)
{
    for (auto i = p; i != r; i++) push_heap(p,next(i));
    for (auto i = r; i != p; i--)  pop_heap(p,i);
}

#ifndef NENTRY
int main()
{
    vector<int> v = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9};
    heap_sort(begin(v), end(v));
    assert(is_sorted(begin(v), end(v)));
}
#endif

