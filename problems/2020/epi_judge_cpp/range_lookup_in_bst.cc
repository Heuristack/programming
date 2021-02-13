#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::unique_ptr;
using std::vector;

struct Interval { int left, right; };

void RangeLookupInBSTHelper(unique_ptr<BstNode<int>> const & tree, Interval const & interval, vector<int> & result)
{
  if (!tree) return;
  if (interval.left <= tree->data && tree->data <= interval.right) {
    RangeLookupInBSTHelper(tree->left,interval,result);
    result.emplace_back(tree->data);
    RangeLookupInBSTHelper(tree->right,interval,result);
    return;
  }
  if (tree->data < interval.left) {
    RangeLookupInBSTHelper(tree->right,interval,result);
    return;
  }
  if (tree->data > interval.right) {
    RangeLookupInBSTHelper(tree->left,interval,result);
    return;
  }
}

vector<int> RangeLookupInBST(unique_ptr<BstNode<int>> const & tree, Interval const & interval)
{
  vector<int> values;
  RangeLookupInBSTHelper(tree,interval,values);
  return values;
}

namespace test_framework {
template <>
struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("length({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Interval& x) {
    return {x.right - x.left};
  }
};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "interval"};
  return GenericTestMain(args, "range_lookup_in_bst.cc",
                         "range_lookup_in_bst.tsv", &RangeLookupInBST,
                         DefaultComparator{}, param_names);
}
