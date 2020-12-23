#include <memory>
#include <vector>
#include <queue>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;
using std::queue;

vector<vector<int>> BinaryTreeDepthOrder(const unique_ptr<BinaryTreeNode<int>>& tree)
{
  vector<vector<int>> levels;
  vector<int> nodes;
  int depth = 0;
  queue<BinaryTreeNode<int>*> q;
  if (tree.get() != nullptr) q.push(tree.get());
  int num = q.size();
  while (!q.empty()) {
    auto n = q.front();
    nodes.push_back(n->data);
    q.pop();
    num--;
    if (n->left)  q.push(n->left.get());
    if (n->right) q.push(n->right.get());
    if (!num) {
      num = q.size();
      depth++;
      levels.emplace_back(std::move(nodes));
    }
  }
  return levels;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
