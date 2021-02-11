#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"

using std::unique_ptr;
using std::vector;

auto FindKLargestInBST0(unique_ptr<BstNode<int>> const & tree, int k, vector<int> & v)
{
  if (!tree) return;
  if (v.size() < k) FindKLargestInBST0(tree->right,k,v);
  if (v.size() < k) v.emplace_back(tree->data);
  if (v.size() < k) FindKLargestInBST0(tree->left,k,v);
}

vector<int> FindKLargestInBST(unique_ptr<BstNode<int>> const & tree, int k)
{
  vector<int> v;
  FindKLargestInBST0(tree,k,v);
  return v;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}

