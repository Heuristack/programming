#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int FindClosestElementsInSortedArrays(vector<vector<int>> const & sorted_arrays)
{
  // note : skip ...
  return 0;
}

int main(int argc, char* argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "minimum_distance_3_sorted_arrays.cc",
                         "minimum_distance_3_sorted_arrays.tsv",
                         &FindClosestElementsInSortedArrays,
                         DefaultComparator{}, param_names);
}

