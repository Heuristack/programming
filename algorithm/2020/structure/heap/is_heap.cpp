#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template <typename iterator> auto parent(iterator b, iterator i, iterator e) {  if (auto r = b + (distance(b,i)+1)/2 - 1; r >= b && r < e ) return r; return e; }
template <typename iterator> auto lchild(iterator b, iterator i, iterator e) {  if (auto r = b + (distance(b,i)+1)*2 - 1; r >= b && r < e ) return r; return e; }
template <typename iterator> auto rchild(iterator b, iterator i, iterator e) {  if (auto r = b + (distance(b,i)+1)*2 + 0; r >= b && r < e ) return r; return e; }

template <typename iterator>
bool is_heap_naive(iterator p, iterator r)
{
    for (iterator i = p; i < r; i++) {
        if (auto pi = parent(p,i,r); pi != r && *pi < *i) {
            return false;
        }
    }
    return true;
}

template <typename iterator>
auto traverse(iterator p, iterator r) -> void
{
    for (iterator i = p; i < r; i++) {
        auto pi = parent(p,i,r);
        auto li = lchild(p,i,r);
        auto ri = rchild(p,i,r);
        cout << "(" << *i << ")";
        if (pi != r) cout << ":" << *pi;
        if (li != r) cout << ":" << *li;
        if (ri != r) cout << "," << *ri;
        cout << endl;
    }
}

int main()
{
    vector<int> heap = {3,1,4,1,5,9,2,6};
    make_heap(begin(heap),end(heap));
    traverse(begin(heap),end(heap));
    assert(is_heap(begin(heap),end(heap)) == is_heap_naive(begin(heap),end(heap)));
}
