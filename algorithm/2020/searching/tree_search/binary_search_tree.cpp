#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#include <iostream>

using namespace std;

#include "binary_tree/binary_tree.hpp"
#include "binary_tree/data.ipp"
#include "traverse.ipp"
#include "property.ipp"
#include "search.ipp"

int main()
{
    using node_type = node<int>;
    node_type * tree = binary_tree_3();

    // note : BFS top-down explore
    vector<node_type> levels;
    binary_search_tree_explore<node_type>(tree, [&levels](node_type * n){
        levels.push_back(*n);
    });
    for (auto const & n : levels) {
        cout << n;
    }
    cout << endl;

    // note : DFS in-order traverse
    vector<node_type> in_order;
    binary_search_tree_traverse<node_type>(tree, [&in_order](node_type * n){
        in_order.push_back(*n);
    });
    for (auto const & n : in_order) {
        cout << n;
    }
    cout << endl;

    // note : DFS in-order path is sorted -> BST
    cout << is_sorted(begin(in_order),end(in_order),[](auto const & a, auto const & b){
        return a.value < b.value;
    }) << endl;

    // note : DFS to verify BST property
    cout << is_binary_search_tree<node_type>(tree) << endl;
    if (auto n = binary_search_tree_search<node_type>(tree,53); n) {
        cout << n->value << endl;
    }
}

