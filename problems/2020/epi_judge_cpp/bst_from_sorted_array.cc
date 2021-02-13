#include <iterator>
#include <vector>
#include <memory>
#include <iostream>

#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::make_unique;
using std::unique_ptr;
using std::vector;
using std::cout;
using std::endl;

unique_ptr<BstNode<int>> BuildMinHeightBSTFromSortedArray(vector<int> const & a)
{
  auto p = begin(a), q = end(a);
  auto d = distance(p,q);
  if (d <= 0) return {};
  auto m = next(p, d/2);
  return make_unique<BstNode<int>>(*m,
    BuildMinHeightBSTFromSortedArray(vector<int>(p,m)),
    BuildMinHeightBSTFromSortedArray(vector<int>(next(m),q)));
}

int BuildMinHeightBSTFromSortedArrayWrapper(TimedExecutor& executor, const vector<int>& A)
{
  auto result =
      executor.Run([&] { return BuildMinHeightBSTFromSortedArray(A); });

  if (test_framework::GenerateInorder(result) != A) {
    throw TestFailure("Result binary tree mismatches input array");
  }
  return test_framework::BinaryTreeHeight(result);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "bst_from_sorted_array.cc",
                         "bst_from_sorted_array.tsv",
                         &BuildMinHeightBSTFromSortedArrayWrapper,
                         DefaultComparator{}, param_names);
}

