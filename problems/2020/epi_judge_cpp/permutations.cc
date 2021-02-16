#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"

using std::iterator_traits;
using std::vector;

// note : this method is too slow to compute even 8-permutation, requires a good algo

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

auto generate_permutation(vector<int> s, int n, vector<vector<int>> & permutations, vector<int> & path) -> vector<vector<int>>
{
    if (!n) {
        permutations.push_back(path);
        return permutations;
    }

    for (auto i = begin(s); i != end(s); i++) {
        path.push_back(*i);
        generate_permutation(remove_copy_it(begin(s),end(s),i),n-1,permutations,path);
        path.pop_back();
    }

    return permutations;
}

vector<vector<int>> Permutations(vector<int> A)
{
  vector<vector<int>> permutations;
  vector<int> path; // note: n-path (track) is n-permutation

  return generate_permutation(A,A.size(),permutations,path);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "permutations.cc", "permutations.tsv",
                         &Permutations, UnorderedComparator{}, param_names);
}

