#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::swap;
using std::find_if;

vector<int> NextPermutation(vector<int> perm)
{
  int k = perm.size() - 2;
  while (k >= 0 && perm[k] >= perm[k+1]) k--;
  if (k == -1) return {};
  swap(*find_if(rbegin(perm),rend(perm),[&](int a) {
        return a > perm[k];
  }),perm[k]);
  reverse(begin(perm) + k + 1, end(perm));
  return perm;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm"};
  return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                         &NextPermutation, DefaultComparator{}, param_names);
}

