#include <iostream>
#include <limits>

using namespace std;

#include "binary_search_tree.hpp"
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

    binary_search_tree_traverse<node_type>(tree); cout << endl;
    cout << is_binary_search_tree<node_type>(tree) << endl;
    if (auto n = binary_search_tree_search<node_type>(tree,53); n) {
        cout << n->value << endl;
    }
}

