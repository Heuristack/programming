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

template <typename graph, typename node = typename graph::node_type, typename edge = typename graph::edge_type>
auto prim(graph const & g, node const & s)
{
    using weight = typename weight_type<edge>::type;
    using prop = mixin<node, parent<node>, length<weight>>;
    extractable<searchable<insertable<vector<prop>>>> open;
    for_each_node(g,[&open](auto const & n){
        open.insert(prop(n.v,decltype(n.v)(),numeric_limits<weight>::max()));
    });
    open.get(s).l = 0;
    insertable<vector<edge>> edges;
    while (!open.empty()) {
        auto u = open.template extract_min<typename prop::length_less>();
        if (u != s) edges.insert(edge(u.p,u.v,u.l));
        for (auto const & e : const_cast<graph&>(g)[u]) {
            if (!open.contains(node(e.t))) continue;
            if (auto & v = open.get(node(e.t)); e.w < v.l) {
                v.l = e.w;
                v.p = e.s;
            }
        }
    }
    return edges;
}

template <typename graph, typename node = typename graph::node_type, typename edge = typename graph::edge_type>
auto prim(graph const & g)
{
    using weight = typename weight_type<edge>::type;
    insertable<vector<edge>> minimum_spanning_tree;
    weight minimum_weight = numeric_limits<weight>::max();
    for_each_node(g,[&](auto const & n){
        insertable<vector<edge>> spanning_tree_edges(0);
        weight spanning_tree_weight = 0;
        for (auto const & e : prim(g,n)) {
            spanning_tree_edges.insert(e);
            spanning_tree_weight += e.w;
        }
        if (spanning_tree_weight < minimum_weight) {
            minimum_spanning_tree = spanning_tree_edges;
            minimum_weight = spanning_tree_weight;
        }
    });
    return minimum_spanning_tree;
}

