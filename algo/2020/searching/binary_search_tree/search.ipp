template <typename node_t>
auto binary_search_tree_search(typename node_t::link_type tree, typename node_t::data_type v) -> typename node_t::link_type
{
    if (!tree) return nullptr;
    else if (v < tree->value) return binary_search_tree_search<node_t>(tree->ltree,v);
    else if (v > tree->value) return binary_search_tree_search<node_t>(tree->rtree,v);
    else return tree;
}

