#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

template <typename iterator, typename inserter>
auto remove_copy_it(iterator p, iterator r, inserter b, iterator k) -> void
{
    for (auto i = p; i != r; i++) {
        if (i != k) {
            *b++ = *i;
        }
    }
}

template <typename iterator, typename return_type = vector<typename iterator_traits<iterator>::value_type>>
auto remove_copy_it(iterator p, iterator r, iterator k) -> return_type
{
    return_type v;
    remove_copy_it(p,r,back_inserter(v),k);
    return v;
}

#include "generate_permutation.ipp"
#include "constraint_satisfaction_problem.ipp"

int main()
{
    for (auto const & s : generate_permutation({1,2,3,4,5},3)) {
        for (auto const & e : s) cout << e;
        cout << " ";
    }
    cout << endl;
    for (auto const & s : permutation({1,2,3,4,5},3).generate()) {
        for (auto const & e : s) cout << e;
        cout << " ";
    }
    cout << endl;
}

