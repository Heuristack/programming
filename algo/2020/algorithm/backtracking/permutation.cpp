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
auto remove_clone_it(iterator p, iterator r, iterator k) -> return_type
{
    return_type v;
    remove_copy_it(p,r,back_inserter(v),k);
    return v;
}

auto permute(vector<int> s, int n) -> vector<vector<int>> // note : generate all n-permutation(s) of set s
{
    static vector<vector<int>> permutations;
    static vector<int> path;

    if (!n) {
        permutations.push_back(path);
        return permutations;
    }

    for (auto i = begin(s); i != end(s); i++) {
        path.push_back(*i);
        permute(remove_clone_it(begin(s),end(s),i),n-1);
        path.pop_back();
    }

    return permutations;
}

int main()
{
    for (auto const & s : permute({1,2,3},2)) {
        for (auto const & e : s) cout << e;
        cout << endl;
    }
}

