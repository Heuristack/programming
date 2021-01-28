#include <algorithm>
#include <utility>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::swap;

void ApplyPermutation0(vector<int> perm, vector<int> * A_ptr)
{
  if (!A_ptr || A_ptr->empty()) return;
  vector<int> & A = *A_ptr;
  vector<int> B(A.size());
  for (int i = 0; i < perm.size(); i++) {
    B[perm[i]] = A[i];
  }
  A = B;
  return;
}

void ApplyPermutation(vector<int> perms, vector<int> * A_ptr)
{
  if (!A_ptr || A_ptr->empty()) return;
  vector<int> & A = *A_ptr;
  for (int i = 0; i < perms.size(); i++) {
    int k = i;
    while (perms[k] >= 0) {
      swap(A[i],A[perms[k]]);
      int t = perms[k];
      perms[k] -= perms.size();
      k = t;
    }
  }
  for (auto & e : perms) { e += perms.size(); }
  return;
}

vector<int> ApplyPermutationWrapper(const vector<int>& perm, vector<int> A)
{
  ApplyPermutation(perm, &A);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}

