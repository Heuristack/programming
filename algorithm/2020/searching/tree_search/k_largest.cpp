#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#include <iostream>

using namespace std;

#include "binary_tree/binary_tree.hpp"
#include "binary_tree/data.ipp"
#include "traverse.ipp"

template <typename node_t, typename data_t = typename node_t::data_type>
auto k_largest(node_t * tree, int k, vector<data_t> & v)
{
    if (!tree) return;
    if (v.size() < k) k_largest(tree->rtree, k, v);
    if (v.size() < k) v.emplace_back(tree->value);
    if (v.size() < k) k_largest(tree->ltree, k, v);
}

int main()
{
    using node_type = node<name_data>;

    node_type * tree = binary_tree_4();
    binary_search_tree_traverse_reverse<node_type>(tree,[](node_type * n){ cout << *n; });
    cout << endl;

    vector<typename node_type::data_type> v;
    k_largest(tree,5,v);
    for (auto const & e : v) cout << "(" << e << ")";
    cout << endl;
}

