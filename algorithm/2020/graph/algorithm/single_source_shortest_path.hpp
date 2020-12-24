template <typename node, typename edge>
auto relax(node const & u, node & v, edge const & e)
{
    assert((e.s == u.v) && (e.t == v.v));
    if (u.l + e.w < v.l) {
        v.l = u.l + e.w;
        v.p = u.v;
    }
}

template <typename graph, typename node = typename graph::node_type, typename edge = typename graph::edge_type>
auto dijkstra(graph const & g, node const & n)
{
    using weight = typename weight_type<edge>::type;
    using prop = mixin<node, parent<node>, length<weight>>;
    searchable<map<node,prop>> close;
    close[n] = prop(n,n.v,0);
    sequential<priority_queue<prop,vector<prop>,typename prop::length_greater>> open;
    open.put(close[n]);
    while (!open.empty()) {
        auto & u = close[static_cast<node>(open.get())];
        for (auto const & e : const_cast<graph&>(g)[u]) {
            if (auto v = node(e.t); !close.contains(v)) {
                close[v] = prop(v.v,u.v,u.l+e.w);
                open.put(close[v]);
            }
            else {
                relax(u,close[v],e);
            }
        }
    }
    return close;
}

template <typename graph, typename node = typename graph::node_type, typename edge = typename graph::edge_type>
auto bellman_ford(graph const & g, node const & n)
{
    using weight = typename weight_type<edge>::type;
    using prop = mixin<node, parent<node>, length<weight>>;

    searchable<map<node,prop>> nodes;
    for_each_node(g,[&nodes](auto const & n){
        nodes[n] = prop(n,n.v,numeric_limits<weight>::max());
    });
    nodes[n].l = 0;

    for (int i = 0; i < g.size(); i++)
    for_each_edge(g,[&nodes](auto const & e){
        relax(nodes[e.s],nodes[e.t],e);
    });

    for_each_edge(g,[&nodes](auto const & e){
        if (nodes.empty()) return;
        if (nodes[e.t].l > nodes[e.s].l + e.w) {
            nodes.clear();
        }
    });

    return nodes;
}
