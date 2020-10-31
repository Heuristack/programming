template <typename node, typename edge>
auto relax(node & u, node & v, edge & e)
{
    assert((e.s == u.v) && (e.t == v.v));
    if (u.l + e.w < v.l) {
        v.l = u.l + e.w;
        v.p = u.v;
    }
}

template <typename graph, typename node = typename graph::node_type, typename edge = typename graph::edge_type>
auto bellman_ford(graph const & g, node const & n)
{
    using weight = typename weight_type<edge>::type;
    using prop = mixin<node, parent<node>, length<weight>>;

    searchable<map<node,prop>> nodes;
    for (auto const & [n,_] : g) {
        nodes[n] = prop(n,n.v,numeric_limits<weight>::max());
    }
    nodes[n].l = 0;

    for (int i = 0; i < g.size(); i++)
    for (auto const & [n,v] : g) {
        for (auto const & e : v) {
            relax(nodes[e.s],nodes[e.t],e);
        }
    }

    for (auto const & [n,v] : g) {
        for (auto const & e : v) {
            if (nodes[e.t].l > nodes[e.s].l + e.w) {
                nodes.clear();
                break;
            }
        }
    }

    return nodes;
}
