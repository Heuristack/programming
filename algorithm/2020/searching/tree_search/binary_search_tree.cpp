#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#include <iostream>

using namespace std;

#include "binary_tree/binary_tree.hpp"
#include "traverse.ipp"
#include "property.ipp"
#include "search.ipp"

int main()
{
    using node_type = node<int>;
    typename node_type::link_type tree =
        new node_type(19,
            new node_type(7,
                new node_type(3,
                    new node_type(2),
                    new node_type(5)),
                new node_type(11,
                    nullptr,
                    new node_type(17,
                        new node_type(13),
                        new node_type(20)))), // breaks BST property
            new node_type(43,
                new node_type(23,
                    nullptr,
                    new node_type(37,
                        new node_type(29,
                            nullptr,
                            new node_type(31)),
                        new node_type(41))),
                new node_type(47,
                    nullptr,
                    new node_type(53))));

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

