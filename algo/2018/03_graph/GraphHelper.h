#ifndef GRAPH_HELPER_H
#define GRAPH_HELPER_H

#include "Graph.h"
#include "GraphData.h"
#include <tuple>
#include <limits>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;

using Vertex = string;
using Weight = double;
using Node = BasicNode<Vertex, Weight>;
using Edge = BasicEdge<Vertex, Weight>;
template<typename E> using Set = set<E>;
template<typename K, typename V> using Map = map<K,V>;

template <int> struct NodeWeight: true_type {};
template <int> struct EdgeWeight: true_type {};
template <int> struct EdgeDirect: true_type {};

template <> struct NodeWeight<0>: false_type {};
template <> struct EdgeWeight<0>: false_type {};
template <> struct EdgeDirect<0>: false_type {};

template <typename EdgeDirectType = EdgeDirect<0>, typename NodeWeightType = NodeWeight<0>, typename EdgeWeightType = EdgeWeight<0>>
struct GraphCreator
{
    using GraphType = BasicGraph<Node,Edge,Set,Map>;

    GraphType make_graph();
};

// TODO : these look odd and ugly, change this to better one

struct UndirectedUnweightedGraph : BasicGraph<Vertex,Vertex,Set,Map> {};
struct DirectedUnweightedGraph : BasicGraph<Vertex,Vertex,Set,Map> {};
struct UndirectedWeightedGraph : BasicGraph<Vertex,Edge,Set,Map> {};
struct DirectedWeightedGraph : BasicGraph<Vertex,Edge,Set,Map> {};

template<typename Graph> Graph make_graph(vector<pair<int,int>> const & edges) { Graph g; return g; }
template<> UndirectedUnweightedGraph make_graph(vector<pair<int,int>> const & edges)
{
    UndirectedUnweightedGraph g;
    for (auto const & [u,v] : edges) {
        g[to_string(u)].insert(to_string(v));
        g[to_string(v)].insert(to_string(u));
    }
    return g;
}
template<> DirectedUnweightedGraph make_graph(vector<pair<int,int>> const & edges)
{
    DirectedUnweightedGraph g;
    for (auto const & [u,v] : edges) {
        g[to_string(u)].insert(to_string(v));
    }
    return g;
}

template <typename Graph> Graph make_graph(vector<pair<pair<string,string>,double>> const & edges) { Graph g; return g; }
template<> UndirectedWeightedGraph make_graph(vector<pair<pair<string,string>,double>> const & edges)
{
    UndirectedWeightedGraph g;
    for (auto const & [e,w] : edges) { auto const & [u,v] = e;
        g[u].insert({u,v,w});
        g[v].insert({v,u,w});
    }
    return g;
};
template<> DirectedWeightedGraph make_graph(vector<pair<pair<string,string>,double>> const & edges)
{
    DirectedWeightedGraph g;
    for (auto const & [e,w] : edges) { auto const & [u,v] = e;
        g[u].insert({u,v,w});
    }
    return g;
};

template <typename Graph> Graph make_graph(istream & s) { Graph g; return g; }
template <> DirectedUnweightedGraph make_graph<DirectedUnweightedGraph>(istream & s)
{
    DirectedUnweightedGraph g;
    for (Vertex source, target; s >> source >> target;) {
        g[source].insert(target);
    }
    return g;
}

template <> UndirectedUnweightedGraph make_graph<UndirectedUnweightedGraph>(istream & s)
{
    UndirectedUnweightedGraph g;
    for (Vertex source, target; s >> source >> target;) {
        g[source].insert(target);
        g[target].insert(source);
    }
    return g;
}

template<> DirectedWeightedGraph make_graph<DirectedWeightedGraph>(istream & s)
{
    DirectedWeightedGraph g;
    for (Edge e; s >> e;) {
        g[e.source].insert(e);
        g[e.target].insert({});
    }
    return g;
}

template<> UndirectedWeightedGraph make_graph<UndirectedWeightedGraph>(istream & s)
{
    UndirectedWeightedGraph g;
    for (Edge e; s >> e;) {
        g[e.source].insert(e);
        g[e.target].insert(Edge{e.target,e.source,e.weight});
    }
    return g;
}

#endif

