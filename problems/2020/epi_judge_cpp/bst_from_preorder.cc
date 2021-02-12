#include <algorithm>
#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"

using std::make_unique;
using std::unique_ptr;
using std::vector;
using std::find_if;

unique_ptr<BstNode<int>> RebuildBSTFromPreorder(vector<int> const & preorder_sequence)
{
  unique_ptr<BstNode<int>> n;
  if (preorder_sequence.empty()) return n;
  n = make_unique<BstNode<int>>(*begin(preorder_sequence));
  auto first_greater = find_if(begin(preorder_sequence),end(preorder_sequence),
      [&preorder_sequence](auto i){ return i > *begin(preorder_sequence); });
  vector<int> ltree_sequence(next(begin(preorder_sequence)),first_greater);
  vector<int> rtree_sequence(first_greater,end(preorder_sequence));
  auto ltree = RebuildBSTFromPreorder(ltree_sequence);
  auto rtree = RebuildBSTFromPreorder(rtree_sequence);
  n->left = move(ltree);
  n->right = move(rtree);
  return n;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder_sequence"};
  return GenericTestMain(args, "bst_from_preorder.cc", "bst_from_preorder.tsv",
                         &RebuildBSTFromPreorder, DefaultComparator{},
                         param_names);
}

