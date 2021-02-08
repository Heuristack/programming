#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::nth_element;
using std::sort;

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.

int FindKthLargest(int k, vector<int>* A_ptr)
{
  if (!A_ptr || A_ptr->empty()) return 0;
  auto & A = *A_ptr;
  sort(begin(A),end(A),[](auto const & a, auto const & b){ return a > b; });
  return A[k-1];
}

int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}

