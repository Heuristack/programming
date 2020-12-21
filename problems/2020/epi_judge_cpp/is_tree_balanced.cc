#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <cmath>


int TreeHeight(const unique_ptr<BinaryTreeNode<int>>& tree)
{
  if (tree == nullptr) return 0;
  auto lh = TreeHeight(tree->left);
  auto rh = TreeHeight(tree->right);
  if (lh < 0 || rh < 0 || std::abs(lh-rh) > 1) return -1;
  else return std::max(lh,rh) + 1;
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree)
{
  return TreeHeight(tree) >= 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
