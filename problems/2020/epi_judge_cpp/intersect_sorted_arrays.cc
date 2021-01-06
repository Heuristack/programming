#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(vector<int> const & A, vector<int> const & B)
{
  vector<int> v;
  auto pa = begin(A), ea = end(A);
  auto pb = begin(B), eb = end(B);
  while ((pa != ea) && (pb != eb)) {
    if (*pa == *pb) {
      if (v.empty() || v.back() != *pa)
        v.push_back(*pa);
      pa++; pb++;
    }
    else if (*pa < *pb) pa++;
    else pb++;
  }
  return v;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}

