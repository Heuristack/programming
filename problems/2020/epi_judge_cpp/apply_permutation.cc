#include <algorithm>
#include <utility>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::swap;

void CyclicPermutation(vector<int> perm, vector<int> * A_ptr, int s);

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

void ApplyPermutation1(vector<int> perm, vector<int> * A_ptr)
{
  if (!A_ptr || A_ptr->empty()) return;
  vector<int> & A = *A_ptr;
  for (int i = 0; i < perm.size(); i++) {
    int k = i;
    while (perm[k] >= 0) {
      swap(A[i],A[perm[k]]);
      int t = perm[k];
      perm[k] -= perm.size();
      k = t;
    }
  }
  for (auto & e : perm) { e += perm.size(); }
  return;
}

void ApplyPermutation(vector<int> perm, vector<int> * A_ptr)
{
  if (!A_ptr || A_ptr->empty()) return;
  vector<int> & A = *A_ptr;
  for (int i = 0; i < A.size(); i++) {
    int k = i;
    while (perm[k] != i) {
      k = perm[k];
      if (k < i) {
        break;
      }
    }
    if (i > k) continue;
    CyclicPermutation(perm,A_ptr,i);
  }
}

void CyclicPermutation(vector<int> perm, vector<int> * A_ptr, int s)
{
  vector<int> & A = *A_ptr;
  int k = s;
  while (perm[k] != s) {
    swap(A[s],A[perm[k]]);
    k = perm[k];
  }
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

