template <typename node_t, typename vistor_t>
auto binary_search_tree_traverse(typename node_t::link_type tree, vistor_t f)
{
    if (!tree) return;
    binary_search_tree_traverse<node_t>(tree->ltree,f);
    f(tree);
    binary_search_tree_traverse<node_t>(tree->rtree,f);
}

template <typename node_t, typename vistor_t>
auto binary_search_tree_explore(typename node_t::link_type tree, vistor_t f)
{
    queue<typename node_t::link_type> q;
    q.push(tree);
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (!p) continue;
        f(p);
        q.push(p->ltree);
        q.push(p->rtree);
    }
}

