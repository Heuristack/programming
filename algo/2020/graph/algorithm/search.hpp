template <template <typename> typename container, typename graph, typename visitor>
auto search(graph const & g, typename graph::node_type const & n, visitor const & f) -> void
{
    using node = typename graph::node_type;
    using edge = typename graph::edge_type;
    using weight = typename weight_type<edge>::type;
    using prop = mixin<node, parent<node>, length<weight>, status, access<>>;

    if (!g.contains(n)) return;

    typename access<>::time_type time = 0;
    searchable<map<node,prop>> close;
    close[n] = prop(n);
    container<prop> open;
    open.put(close[n]);
    while (!open.empty()) {
        auto & u = close[static_cast<node>(open.get())];
        u.s = status::expanding;
        u.enter = time++;
        invoke(f,u);
        for (auto const & e : const_cast<graph&>(g)[u]) {
            if (auto v = node(e.t); !close.contains(v)) {
                weight w = 1;
                if constexpr (is_weighted<edge>::value) {
                    w = e.w;
                }
                close[v] = prop(v.v,u.v,u.l+w,status::discovered,0);
                open.put(close[v]);
            }
        }
        u.s = status::processed;
        u.leave = time++;
        invoke(f,u);
    }
}

template <typename graph, typename visitor>
auto DFS(graph const & g, typename graph::node_type const & u, visitor const & c) -> void
{
    static typename access<>::time_type time = 0;
    static searchable<set<typename graph::node_type>> close;
    if (!g.contains(u)) return;
    close.insert(u);
    invoke(c,u,status::expanding,time++);
    for (auto const & e : const_cast<graph&>(g)[u]) {
        if (auto v = typename graph::node_type(e.t); !close.contains(v)) {
            DFS(g,v,c);
        }
    }
    invoke(c,u,status::processed,time++);
}

namespace strategies
{
    enum class DFS;
    enum class BFS;
    enum class BST;

    template <typename strategy> struct container
    {
        template <typename node> using type = sequential<typename conditional<is_same<strategy,strategies::DFS>::value,stack<node>,queue<node>>::type>;
    };
    template<> struct container<BST>
    {
        template <typename node> using type = sequential<priority_queue<node,vector<node>,typename node::length_greater>>;
    };
}

