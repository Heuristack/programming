#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"

using std::unique_ptr;
using std::vector;

void FindKLargestInBST0(unique_ptr<BstNode<int>> const & tree, int k, vector<int> & largests)
{
  if (!tree) return;
  if (largests.size() < k) FindKLargestInBST0(tree->right, k, largests);
  if (largests.size() < k) largests.emplace_back(tree->data);
  if (largests.size() < k) FindKLargestInBST0(tree->left,  k, largests);
}

vector<int> FindKLargestInBST(unique_ptr<BstNode<int>> const & tree, int k)
{
  vector<int> largests;
  FindKLargestInBST0(tree,k,largests);
  return largests;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}

