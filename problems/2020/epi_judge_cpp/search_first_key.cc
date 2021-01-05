#include <algorithm>
#include <vector>
#include <cassert>

#include "test_framework/generic_test.h"
using std::vector;
using std::lower_bound;
using std::is_sorted;

int SearchFirstOfK0(const vector<int>& A, int k)
{
  assert(is_sorted(begin(A),end(A)));
  auto e = lower_bound(begin(A),end(A),k);
  if (e != end(A) && *e == k ) return e - begin(A);
  return -1;
}

int SearchFirstOfK(vector<int> const & A, int k)
{
  if (A.empty()) return -1;
  int p = 0, q = size(A) - 1;
  int d = q - p + 1;
  int m = p + d/2;
  int e = -1;
  while (d > 0) {
    if (k < A[m]) { q = m - 1; }
    else if (k == A[m]) { e = m; q = m - 1; }
    else { p = m + 1; }
    d = q - p + 1;
    m = p + d/2;
  }
  return e;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}

