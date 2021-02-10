template <typename node_t>
auto is_binary_search_tree(typename node_t::link_type tree, typename node_t::data_type lower_bound, typename node_t::data_type upper_bound)
{
    if (!tree) return true;
    if (tree->value < lower_bound || tree->value > upper_bound) return false;
    return is_binary_search_tree<node_t>(tree->ltree, lower_bound, tree->value)
        && is_binary_search_tree<node_t>(tree->rtree, tree->value, upper_bound);
}

template <typename node_t>
auto is_binary_search_tree(typename node_t::link_type tree)
{
    return is_binary_search_tree<node_t>(tree,
            numeric_limits<typename node_t::data_type>::min(),
            numeric_limits<typename node_t::data_type>::max());
}

