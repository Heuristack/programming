#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

template <typename vertex, typename weight>
struct basic_node
{
    using vertex_type = vertex;
    using weight_type = weight;
    using this_type = basic_node<vertex_type,weight_type>;

    basic_node(vertex_type v, weight_type w) : v(v), w(w) {}
    basic_node(vertex_type v) : basic_node(v,{}) {}

    bool operator < (this_type const & that) const
    {
        return v < that.v;
    }

    vertex_type v;
    weight_type w;
};

template <typename node>
struct basic_edge
{
    using node_type = node;
    using this_type = basic_edge<node_type>;

    using vertex_type = typename node_type::vertex_type;
    using weight_type = typename node_type::weight_type;

    basic_edge(vertex_type s, vertex_type t, weight_type w) : s(s), t(t), w(w) {}
    basic_edge(vertex_type s, vertex_type t) : basic_edge(s,t,{}) {}
    basic_edge(node_type const & s, node_type const & t, weight_type w) : basic_edge(s.v, t.v, w) {}
    basic_edge(node_type const & s, node_type const & t) : basic_edge(s.v, t.v) {}

    bool operator < (this_type const & that) const
    {
        return t < that.t;
    }

    vertex_type s;
    vertex_type t;
    weight_type w;
};

template <typename node, typename edge, template<typename> typename set, template<typename,typename> typename map>
struct basic_graph : map<node,set<edge>>
{
    using node_type = node;
    using edge_type = edge;

    using set_type = set<edge_type>;
    using map_type = map<node_type,set_type>;

    using vertex_type = typename node_type::vertex_type;
};

template <typename graph, typename function>
auto for_each_node(graph & g, function f)
{
    for (auto & [n,_] : g) {
        f(n);
    }
}

template <typename graph, typename function>
auto for_each_edge(graph & g, function f)
{
    for (auto & [n,_] : g) {
        for (auto & e : _) {
            f(e);
        }
    }
}

template <typename edge> using set_template = std::set<edge>;
template <typename node, typename set> using map_template = std::map<node,set>;
using node = basic_node<string,int>;
using edge = basic_edge<node>;
ostream & operator << (ostream & s, node const & n) { return s << "(" << n.v << ")"; }
ostream & operator << (ostream & s, edge const & e) { return s << "(" << e.s << "," << e.t << ")"; }

using graph = basic_graph<node, edge, set_template, map_template>;
ostream & operator << (ostream & s, graph const & g)
{
    for (auto & [n,_] : g) {
        s << n << ": ";
        for (auto & e : _) {
            cout << e;
        }
        s << "\n";
    }
    return s;
}

int main()
{
    graph g;

    node a("a");
    node b("b");
    node c("c");
    node d("d");

    g[a].insert(edge(a,b));
    g[a].insert(edge(a,c));
    g[b].insert(edge(b,d));
    g[c].insert(edge(c,d));
    g[d];

    for_each_node(g,[](auto const & n){ cout << n << endl; });
    for_each_edge(g,[](auto const & e){ cout << e << endl; });

    cout << g;
}

