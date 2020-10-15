template <typename node_t>
auto traverse(node_t * n) -> map<int,vector<node_t*>>
{
    static map<int,vector<node_t*>> node_map;
    static int depth = 0;
    if (n) {
        node_map[depth++].push_back(n);
        traverse(n->ltree);
        traverse(n->rtree);
        depth--;
    }
    return node_map;
}

