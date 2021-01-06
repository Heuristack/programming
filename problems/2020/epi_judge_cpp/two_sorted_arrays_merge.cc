#include <cassert>
#include <vector>
#include <utility>

#include "test_framework/generic_test.h"
using std::vector;
using std::move;

void MergeTwoSortedArrays(vector<int> & A, int m, const vector<int> & B, int n)
{
  assert(A.size() >= m && B.size() >= n);
  vector<int> v;
  int i = 0, j = 0;
  while (i != m && j != n) {
    if (A[i] <= B[j]) { v.push_back(A[i++]); }
    else { v.push_back(B[j++]); }
  }
  while (i != m) v.push_back(A[i++]);
  while (j != n) v.push_back(B[j++]);
  A = move(v);
}

vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m, const vector<int>& B, int n)
{
  MergeTwoSortedArrays(A, m, B, n);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "m", "B", "n"};
  return GenericTestMain(
      args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
      &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
