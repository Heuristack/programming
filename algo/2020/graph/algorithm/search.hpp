template <template <typename> typename container, typename graph, typename visitor>
auto search(graph const & g, typename graph::node_type const & n, visitor const & c) -> void
{
    using base = typename graph::node_type;
    using node = mixin<base, parent<base>, length<int>, status, access<>>;

    if (!g.contains(n)) return;

    typename access<>::time_type time = 0;
    searchable<map<base,node>> close;
    close[n] = node(n);

    container<base> open;
    open.put(n);
    while (!open.empty()) {
        auto & u = close[open.get()];
        u.s = status::expanding;
        u.enter = time++;
        for (auto const & e : const_cast<graph&>(g)[u]) {
            if (auto v = base(e.t); !close.contains(v)) {
                close[v] = node(v,u.v,u.l+1,{},{});
                open.put(v);
            }
        }
        invoke(c,u);
        u.leave = time++;
        u.s = status::processed;
    }
}

template <typename graph, typename visitor>
auto DFS(graph const & g, typename graph::node_type const & u, visitor const & c) -> void
{
    static searchable<set<typename graph::node_type>> close;
    if (!g.contains(u)) return;
    close.insert(u);
    invoke(c,u);
    for (auto const & e : const_cast<graph&>(g)[u]) {
        if (auto v = node(e.t); !close.contains(v)) {
            DFS(g,v,c);
        }
    }
}

namespace strategies
{
    enum class DFS;
    enum class BFS;

    template <typename strategy>
    struct container
    {
        template <typename node> using type = sequential<typename conditional<is_same<strategy,strategies::DFS>::value,stack<node>,queue<node>>::type>;
    };
}

