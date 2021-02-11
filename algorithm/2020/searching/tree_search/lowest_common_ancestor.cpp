#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#include <iostream>

using namespace std;

#include "binary_tree/binary_tree.hpp"
#include "binary_tree/data.ipp"
#include "search.ipp"

template <typename node_t>
auto lowest_common_ancestor(node_t * tree, node_t * p, node_t * q) -> node_t *
{
    if (!tree) return nullptr;
    while (tree->value < p->value || tree->value > q->value) {
        while (tree->value < p->value) tree = tree->rtree;
        while (tree->value > q->value) tree = tree->ltree;
    }
    return tree;
}

int main()
{
    using node_type = node<name_data>;
    node_type * tree = binary_tree_4();
    auto p = binary_search_tree_search<node_type>(tree,name_data{' ', 3});
    auto q = binary_search_tree_search<node_type>(tree,name_data{' ',17});
    auto l = lowest_common_ancestor(tree,p,q);
    if (l) cout << *l << endl;
}

