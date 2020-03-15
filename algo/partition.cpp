#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

template <typename iterator, typename predicate>
auto partition_forward(iterator p, iterator r, predicate e)
{
    iterator k = p;
    for (iterator i = p; i != r; i++) {
        if (e(*i)) {
            iter_swap(k++,i);
        }
    }
    return k;
}

int main()
{
    vector<int> v {3,1,4,1,5,9};
    auto p = [](auto const & e){ return e > 4; };
    partition_forward(begin(v),end(v),p);
    cout << is_partitioned(begin(v),end(v),p) << endl;
}

