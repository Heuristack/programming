template <typename graph, typename node = typename graph::node_type, typename edge = typename graph::edge_type>
auto kruskal(graph const & g)
{
    static_assert(is_weighted<edge>::value);

    map<node,node> disjoint_sets;
    for_each_node(g,[&disjoint_sets](auto const & n){
        disjoint_sets[n] = n;
    });
    auto find_set = [&disjoint_sets](node u){
        while (u != disjoint_sets[u]) {
            u = disjoint_sets[u];
        }
        return u;
    };
    auto union_set = [&disjoint_sets,&find_set](node u, node v){
        auto ru = find_set(u);
        auto rv = find_set(v);
        disjoint_sets[rv] = ru;
    };

    multiset<edge,typename edge::weight_less> edges;
    for_each_edge(g,[&edges](auto const & e){
        edges.insert(e);
    });

    insertable<vector<edge>> minimum_spanning_tree_edges;
    for (auto const & e : edges) {
        auto u = node(e.s);
        auto v = node(e.t);
        if (find_set(u) != find_set(v)) {
            minimum_spanning_tree_edges.insert(e);
            union_set(u,v);
        }
    }
    return minimum_spanning_tree_edges;
}
