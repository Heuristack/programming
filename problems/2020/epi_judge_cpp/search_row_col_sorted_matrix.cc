#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool MatrixSearch(vector<vector<int>> const & a, int x)
{
  if (a.empty() || a[0].empty()) return 0;
  int m = a.size();
  int n = a.back().size();
  for (int i = 0, j = n - 1; i <= m - 1 && 0 <= j;) {
    if (auto e = a[i][j]; x == e) { return 1; }
    else if (x < e) { j--; }
    else if (x > e) { i++; }
  }
  return 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "x"};
  return GenericTestMain(args, "search_row_col_sorted_matrix.cc",
                         "search_row_col_sorted_matrix.tsv", &MatrixSearch,
                         DefaultComparator{}, param_names);
}

