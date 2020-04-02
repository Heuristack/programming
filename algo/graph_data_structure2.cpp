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
struct edge : weighted<weight> ...
{
    static_assert(sizeof...(weight) <= 1);
    using this_type = node<vertex, weight...>;
    using vertex_type = vertex;

    edge(vertex_type const & s, vertex_type const & t, weight const & ... w) : s(s), t(t), weighted<weight>(w) ... {}
    edge() : weighted<weight>() ... {}

    bool operator < (this_type const & that) const { return tie(s,t) < tie(that.s,that.t); }

    vertex_type s{};
    vertex_type t{};
};

template <typename node, typename edge, template<typename> typename set, template<typename,typename> typename map>
struct graph : map<node,set<edge>>
{
    static_assert(is_same<typename node::vertex_type, typename edge::vertex_type>::value);
    using vertex_type = typename node::vertex_type;
    using node_type = node;
    using edge_type = edge;

    template <typename direction> graph(initializer_list<edge_type> edges) : graph(edges, direction()) {} // note : how to provide argument - templated constructor!
    graph(initializer_list<edge_type> edges, enum class undirect) {}
    graph(initializer_list<edge_type> edges, enum class directed) {}
};
template <typename e> using template_set = set<e>;
template <typename n, typename s> using template_map = map<n,s>;

int main()
{
    using typename_node = node<string,int>;
    using typename_edge = edge<string,int>;
    graph<typename_node,typename_edge,template_set,template_map> g({{"A","B",10},{"B","C",10}},undirect{});
}

