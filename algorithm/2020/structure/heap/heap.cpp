#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <typename iterator>
auto to_string(iterator b, iterator e) -> string
{
    stringstream s;
    for (auto i = b; i != e; i++) {
        s << "(" << (*i) << ")";
    }
    return s.str();
}

int main()
{
    // note : make a heap
    vector<int> heap = {3,1,4,1,5,9,2,6};
    make_heap(begin(heap),end(heap));
    cout << to_string(begin(heap),end(heap)) << endl;

    // note : append 5,3 to heap
    heap.push_back(5);
    heap.push_back(3);
    cout << to_string(begin(heap),end(heap)) << endl;

    // note : the appended 5,3 shouldn't be in heap
    auto heap_end = is_heap_until(begin(heap),end(heap));
    cout << to_string(begin(heap),heap_end) << endl;

    // note : push 5 into the heap
    push_heap(begin(heap),next(heap_end));
    cout << to_string(begin(heap),end(heap)) << endl;

    // note : heap is increased by 2, since 3 is accentally already in heap
    heap_end = is_heap_until(begin(heap),end(heap));
    cout << to_string(begin(heap),heap_end) << endl;

    // note : pop the maximum element out from the heap
    pop_heap(begin(heap),end(heap));
    cout << to_string(begin(heap),end(heap)) << endl;
}
