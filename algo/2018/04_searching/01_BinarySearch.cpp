#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

template<typename Iterator, typename Key>
Iterator binary_search_iterative(Iterator p, Iterator r, Key k)
{
    auto const e = r;
    auto d = distance(p,r);
    auto m = p + d/2;
    while (d > 0) {
        if (k == *m) return m;
        else if (k < *m) r = m;
        else if (k > *m) p = next(m);
        d = distance(p,r);
        m = p + d/2;
    }
    return e;
}

template<typename Iterator, typename Key>
Iterator binary_search_recursive(Iterator p, Iterator r, Key k)
{
    static const auto e = r;
    auto d = distance(p,r);
    auto m = p + d/2;
    if (d <= 0) return e;
    else if (k < *m) return binary_search_recursive(p,m,k);
    else if (k > *m) return binary_search_recursive(next(m),r,k);
    else return m;
}

int main()
{
    vector<int> v = {1,2,3,4,5,6,7,8,9};
    cout << (binary_search_recursive(begin(v), end(v), 5) == end(v)) << endl;
    cout << (binary_search_iterative(begin(v), end(v), 5) == end(v)) << endl;
}

