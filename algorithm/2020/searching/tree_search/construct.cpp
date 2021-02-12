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
auto construct(vector<data_t> const & sequence) -> node_t *
{
    node_t * n = nullptr;
    if (sequence.empty()) { return n; }
    n = new node_t(*begin(sequence));
    auto first_greater = find_if(begin(sequence),end(sequence),[&sequence](auto i){ return (i > (*begin(sequence))); });
    vector<data_t> ltree_seq(next(begin(sequence)),first_greater);
    vector<data_t> rtree_seq(first_greater,end(sequence));
    auto ltree = construct<node_t>(ltree_seq);
    auto rtree = construct<node_t>(rtree_seq);
    n->ltree = ltree;
    n->rtree = rtree;
    return n;
}

int main()
{
    using node_type = node<int>;
    vector<typename node_type::data_type> v {43,23,37,29,31,41,47,53};
    auto tree = construct<node_type>(v);
    binary_search_tree_traverse<node_type>(tree,[](node_type * n){ cout << *n; });
}
