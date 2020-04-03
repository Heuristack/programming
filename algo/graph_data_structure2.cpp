#include <iostream>
#include <string>
#include <set>
#include <map>
#include <initializer_list>

using namespace std;

template <typename weight>
struct weighted
{
    using weight_type = weight;

    explicit weighted(weight_type const & w) : w(w) {}
    weighted() = default;

    weight_type w{};
};

template <typename vertex, typename ... weight>
struct node : weighted<weight> ...
{
    static_assert(sizeof...(weight) <= 1);
    using this_type = node<vertex, weight...>;
    using vertex_type = vertex;

    node(vertex_type const & v, weight const & ... w) : v(v), weighted<weight>(w) ... {}
    node() : weighted<weight>() ... {}

    bool operator < (this_type const & that) const { return v < that.v; }

    vertex_type v{};
};
template <typename vertex, typename ... weight>
auto operator << (ostream & s, node<vertex,weight...> const & n) -> ostream &
{
    return s << "(" << n.v << ")";
}

template <typename vertex, typename ... weight>
struct edge : weighted<weight> ...
{
    static_assert(sizeof...(weight) <= 1);
    using this_type = edge<vertex, weight...>;
    using vertex_type = vertex;

    edge(vertex_type const & s, vertex_type const & t, weight const & ... w) : s(s), t(t), weighted<weight>(w) ... {}
    edge() : weighted<weight>() ... {}
    auto reverse() -> this_type & { swap(s,t); return *this; }

    bool operator < (this_type const & that) const { return tie(s,t) < tie(that.s,that.t); }

    vertex_type s{};
    vertex_type t{};
};
template <typename vertex, typename ... weight>
auto operator << (ostream & s, edge<vertex,weight...> const & e) -> ostream &
{
    string w; if constexpr (sizeof...(weight)) { w = ":" + to_string(e.w); }
    return s << "(" << e.s << "," << e.t << w << ")";
}

template <typename e> using template_set = set<e>;
template <typename n, typename s> using template_map = map<n,s>;

template <typename node, typename edge, template<typename> typename set=template_set, template<typename,typename> typename map=template_map>
struct graph : map<node,set<edge>>
{
    static_assert(is_same<typename node::vertex_type, typename edge::vertex_type>::value);
    using vertex_type = typename node::vertex_type;
    using node_type = node;
    using edge_type = edge;
    using this_type = graph<node,edge,set,map>;
    using base_type = map<node,set<edge>>;

    template <typename direction> static auto make_graph(initializer_list<edge_type> edges) -> this_type // note : how to provide argument - templated constructor!
    {
        return graph(edges,direction());
    }

    graph(initializer_list<edge_type> edges, enum class   directed) { for (auto const & e : edges) insert_edge(e.s,e); }
    graph(initializer_list<edge_type> edges, enum class undirected) { for (auto const & e : edges) insert_edge(e); }

    auto insert_edge(vertex_type const & v, edge_type const & e) { base_type::operator[](node_type(v)).insert(e); }
    auto insert_edge(edge_type const & e) { insert_edge(e.s,e); insert_edge(e.t,edge_type{e}.reverse()); }
};

template <typename graph, template <typename> typename visitor>
auto for_each(graph const & g, visitor<typename graph::node_type> bn, visitor<typename graph::edge_type> ce, visitor<typename graph::node_type> an)  // note : this doesn't work - make it work!
{
    for (auto const & [n,v] : g) {
        invoke(bn,n);
        for (auto const & e : v) {
            invoke(ce,e);
        }
        invoke(an,n);
    }
}

template <typename graph, typename bnvistor, typename evistor, typename anvister>
auto for_each(graph const & g, bnvistor bn, evistor ce, anvister an)
{
    for (auto const & [n,v] : g) {
        invoke(bn,n);
        for (auto const & e : v) {
            invoke(ce,e);
        }
        invoke(an,n);
    }
}

template <typename node, typename edge, template<typename> typename set, template<typename,typename> typename map>
auto operator << (ostream & s, graph<node,edge,set,map> const & g) -> ostream &
{
    for_each(g,
        [&s](auto const & n){ s << n << ":"; },
        [&s](auto const & e){ s << e; },
        [&s](auto const & n){ s << "\n"; }
    );
    return s;
}

template <typename graph, typename visitor>
auto dfs(graph const & g, typename graph::node_type const & u, visitor const & c) -> void
{
    static set<typename graph::node_type> closed;
    invoke(c,u);
    closed.insert(u);
    for (auto const & e : const_cast<graph&>(g)[u]) {
        auto v = node(e.t);
        if (closed.find(v)==closed.end())
            dfs(g,v,c);
    }
}

int main()
{
//  auto g = graph<node<string>,edge<string,int>>::make_graph<undirected>({
//      {"A","B", 4}, {"A","H", 8},
//      {"B","H",11}, {"B","C", 8},
//      {"H","I", 7}, {"H","G", 1},
//      {"I","C", 2}, {"I","G", 6},
//      {"C","D", 7}, {"C","F", 4},
//      {"G","F", 2},
//      {"D","F",14}, {"D","E", 9},
//      {"E","F",10},
//  });
    auto g = graph<node<int>,edge<int>>::make_graph<undirected>({
        {1,6}, {1,2}, {1,5},
        {2,5}, {2,3},
        {5,4},
        {3,4},
    });
    cout << g;
    dfs(g,{1},[](auto const & n){ cout << n; }); cout << endl;
}

