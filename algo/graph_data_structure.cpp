#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <initializer_list>
#include <variant>

using namespace std;

template <typename weight>
struct weighted
{
    using weight_type = weight;

    explicit weighted(weight_type const & w) : w(w) {}
    weighted() = default;

    weight_type w{};
};
template <typename> struct is_weighted {};

template <typename vertex, typename ... weight>
struct node : weighted<weight> ...
{
    static_assert(sizeof...(weight) <= 1);
    using this_type = node<vertex, weight...>;
    using vertex_type = vertex;

    node(vertex_type const & v, weight const & ... w) : v(v), weighted<weight>(w) ... {}
    node() : weighted<weight>() ... {}

    bool operator < (this_type const & that) const { return v < that.v; }       // requires order relation of vertex

    vertex_type v{};
};
template <typename vertex> struct is_weighted<node<vertex>> { static bool constexpr value = false; };
template <typename vertex, typename ... weight> struct is_weighted<node<vertex,weight...>> { static bool constexpr value = true; };
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
template <typename vertex> struct is_weighted<edge<vertex>> { static bool constexpr value = false; };
template <typename vertex, typename ... weight> struct is_weighted<edge<vertex,weight...>> { static bool constexpr value = true; };
template <typename vertex, typename ... weight>
auto operator << (ostream & s, edge<vertex,weight...> const & e) -> ostream &
{
    string w; if constexpr (sizeof...(weight)) { w = ":" + to_string(e.w); }
    return s << "(" << e.s << "," << e.t << w << ")";
}

namespace properties {

template <typename node>
struct parent
{
    using node_type = node;
    using vertex_type = typename node_type::vertex_type;
    parent(vertex_type const & p) : p(p) {}
    parent() = default;
    vertex_type p{};
};

template <typename weight>
struct length
{
    using weight_type = weight;
    length(weight_type const & l) : l(l) {}
    length() = default;
    weight_type l{};
};

struct status
{
    enum status_type { discovered, expanding, processed };
    status(status_type s) : s(s) {}
    status() = default;
    status_type s = discovered;
};

template <typename time = unsigned>
struct access
{
    using time_type = time;
    access() = default;
    time_type enter{};
    time_type leave{};
};

}

template <typename base, typename ... properties>
struct mixin : base, properties ...
{
    using base_type = base;
    mixin(base_type const & b, properties const & ... p) : base_type(b), properties(p) ... {}
    mixin(base_type const & b) : base_type(b) {}
    mixin() : base_type() {}
};

template <typename container>
struct searchable : container
{
    auto contains(typename container::key_type const & k) const { return container::find(k) != container::end(); } // note : C++20 feature!
    auto get(typename container::key_type & k) -> typename container::value_type & { return *container::find(k); }
};

template <typename container>
struct insertable : container
{
    auto insert(typename container::value_type const & v) { return container::push_back(v); }
};

template <typename item> using default_list = insertable<list<item>>;
template <typename key> using default_set = searchable<set<key>>;
template <typename key, typename value> using default_map = searchable<map<key,value>>;

template <typename node, typename edge, template<typename> typename set=default_list, template<typename,typename> typename map=default_map>
struct graph : searchable<map<node,set<edge>>>
{
    static_assert(is_same<typename node::vertex_type, typename edge::vertex_type>::value);
    using vertex_type = typename node::vertex_type;
    using this_type = graph<node,edge,set,map>;
    using base_type = map<node,set<edge>>;
    using node_type = node;
    using edge_type = edge;

    template <typename direction>
    static auto make_graph(initializer_list<edge_type> edges) -> this_type // note : how to provide argument to templated constructor!
    {
        return graph(edges,direction());
    }
    template <typename direction>
    graph(initializer_list<edge_type> edges, direction d)
    {
        for (auto const & e : edges) insert_edge(e,d);
    }

    template <typename direction>
    static auto make_graph(initializer_list<variant<node_type,edge_type>> varis) -> this_type
    {
        return graph(varis,direction());
    }
    template <typename direction>
    graph(initializer_list<variant<node_type,edge_type>> varis, direction d)
    {
        for (auto const & v : varis) { if (holds_alternative<node_type>(v)) insert_node(get<node_type>(v)); if (holds_alternative<edge_type>(v)) insert_edge(get<edge_type>(v),d); }
    }

    auto insert_node(vertex_type const & v) -> set<edge_type> & { return base_type::operator[](node_type(v)); }
    auto insert_node(node_type const & n) { insert_node(n.v); }
    auto insert_edge(vertex_type const & v, edge_type const & e) { insert_node(v).insert(e); }
    auto insert_edge(edge_type const & e, enum class   directed) { insert_edge(e.s,e); }
    auto insert_edge(edge_type const & e, enum class undirected) { insert_edge(e.s,e); insert_edge(e.t,edge_type{e}.reverse()); }
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
    static searchable<set<mixin<typename graph::node_type,properties::parent<typename graph::node_type>>>> close;
    if (!g.contains(u)) return;
    close.insert(u);
    invoke(c,u);
    for (auto const & e : const_cast<graph&>(g)[u]) {
        if (auto v = node(e.t); !close.contains(v)) {
            dfs(g,v,c);
        }
    }
}

template <typename container>
struct adapter : container
{
    using base_type = container;
    using value_type = typename base_type::value_type;
    auto get() -> value_type
    {
        value_type v;
        if constexpr (is_same<base_type,stack<value_type>>::value) { v = base_type::top();   }
        if constexpr (is_same<base_type,queue<value_type>>::value) { v = base_type::front(); }
        base_type::pop();
        return v;
    }
    auto put(value_type const & v)
    {
        base_type::push(v);
    }
};

namespace strategies
{
    enum class dfs;
    enum class bfs;

    template <typename strategy, typename node>
    struct container
    {
        using type = adapter<typename conditional<is_same<strategy,strategies::dfs>::value,stack<node>,queue<node>>::type>;
    };
}

template <typename strategy, typename graph, typename visitor>
auto search(graph const & g, typename graph::node_type const & n, visitor const & c) -> void
{
    using base = typename graph::node_type;
    using node = mixin<base, properties::parent<base>, properties::length<int>, properties::status, properties::access<>>;

    typename properties::access<>::time_type time = 0;
    searchable<map<base,node>> close;
    close[n] = node(n);

    typename strategies::container<strategy,base>::type open;
    open.put(n);
    while (!open.empty()) {
        auto & u = close[open.get()];
        u.s = properties::status::expanding;
        u.enter = time++;
        for (auto const & e : const_cast<graph&>(g)[u]) {
            if (auto v = base(e.t); !close.contains(v)) {
                close[v] = node(v,u.v,u.l+1,{},{});
                open.put(v);
            }
        }
        invoke(c,u);
        u.leave = time++;
        u.s = properties::status::processed;
    }
}

static initializer_list<edge<string,int>> clrs2301 = {
    {"A","B", 4}, {"A","H", 8},
    {"B","H",11}, {"B","C", 8},
    {"H","I", 7}, {"H","G", 1},
    {"I","C", 2}, {"I","G", 6},
    {"C","D", 7}, {"C","F", 4},
    {"G","F", 2},
    {"D","F",14}, {"D","E", 9},
    {"E","F",10},
};

static initializer_list<edge<int>> manual0509 = {
    {1,6}, {1,2}, {1,5},
    {2,5}, {2,3},
    {5,4},
    {3,4},
};

static initializer_list<variant<node<int>,edge<int>>> varis = {
    variant<node<int>,edge<int>>{in_place_index_t<1>{},1,2},
    edge<int>{2,3},
    {4},
//  {5,6}
};

int main()
{
    auto g = graph<node<string>,edge<string,int>>::make_graph<undirected>(clrs2301);
    auto n = node<string>("A");
    auto v = [](auto const & n){ cout << n; };
    dfs(g,n,v); cout << endl;
    search<strategies::dfs>(g,n,v); cout << endl;
    search<strategies::bfs>(g,n,v); cout << endl;

    auto s = graph<node<int>,edge<int>>::make_graph<directed>(varis);
    cout << s;
}

