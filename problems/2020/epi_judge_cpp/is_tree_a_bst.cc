#include <memory>
#include <limits>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::numeric_limits;

bool IsBinaryTreeBST0(const unique_ptr<BinaryTreeNode<int>>& tree, int lower, int upper)
{
  if (!tree.get()) return true;
  if (tree->data < lower || tree->data > upper) return false;
  return IsBinaryTreeBST0(tree->left,lower,tree->data)
      && IsBinaryTreeBST0(tree->right,tree->data,upper);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree)
{
  return IsBinaryTreeBST0(tree,numeric_limits<int>::min(),numeric_limits<int>::max());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
