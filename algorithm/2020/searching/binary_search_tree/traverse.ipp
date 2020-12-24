template <typename node_t>
auto binary_search_tree_traverse(typename node_t::link_type tree)
{
    if (!tree) return;
    binary_search_tree_traverse<node_t>(tree->ltree);
    cout << (*tree);
    binary_search_tree_traverse<node_t>(tree->rtree);
}

