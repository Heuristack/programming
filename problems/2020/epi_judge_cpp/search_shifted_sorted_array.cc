#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchSmallest(const vector<int>& A)
{
  int p = 0, q = A.size() - 1;
  while (p < q) {
    int m = p + (q - p)/2;
    if (A[m] > A[q]) p = m + 1;
    else q = m;
  }
  return p;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}

