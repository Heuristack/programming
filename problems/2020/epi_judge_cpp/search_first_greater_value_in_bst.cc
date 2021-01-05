#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

BstNode<int>* FindFirstGreaterThanK0(unique_ptr<BstNode<int>> const & tree, int k, BstNode<int> * & n)
{
  if (!tree.get()) return n;
  if (tree->data > k) {
    n = tree.get();
    return FindFirstGreaterThanK0(tree->left,k,n);
  }
  else return FindFirstGreaterThanK0(tree->right,k,n);
}

BstNode<int>* FindFirstGreaterThanK(unique_ptr<BstNode<int>> const & tree, int k)
{
  BstNode<int> * n = nullptr;
  return FindFirstGreaterThanK0(tree,k,n);
}

int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>>& tree, int k) {
  auto result = FindFirstGreaterThanK(tree, k);
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "search_first_greater_value_in_bst.cc",
                         "search_first_greater_value_in_bst.tsv",
                         &FindFirstGreaterThanKWrapper, DefaultComparator{},
                         param_names);
}

