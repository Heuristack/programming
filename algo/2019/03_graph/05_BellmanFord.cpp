#include "GraphHelper.h"

template <typename Vertex, typename Weight, typename Edge, typename Graph>
auto BellmanFord(Graph & g, Vertex s) -> vector<tuple<Vertex,Weight,vector<Vertex>>>
{
    struct Node
    {
        Vertex vertex;
        Vertex parent;
        Weight length = numeric_limits<Weight>::max();
    };

    auto relax = [](Node & u, Node & v, Weight w){
        if (v.length > u.length + w) {
            v.length = u.length + w;
            v.parent = u.vertex;
        }
    };

    map<Vertex,Node> open;
    for (auto [v,_] : g) {
        open[v] = Node{v,v};
    }
    open[s].length = 0;

    for (auto i = 0; i < open.size(); i++) {
        for_each_edge(g,[relax,&open](auto const & e){
            relax(open[e.source],open[e.target],e.weight);
        });
    }

    for (auto [u,_] : g) {
        for (auto [u,v,w] : _) {
            if (open[v].length > open[u].length + w) {
                return {};
            }
        }
    }

    vector<tuple<Vertex,Weight,vector<Vertex>>> sssp;
    for (auto [_,n] : open) {
        stack<Vertex> s;
        auto p = n.parent;
        auto v = n.vertex;
        while (p != v) {
            s.push(p);
            v = p;
            p = open[v].parent;
        }
        vector<Vertex> path;
        while (!s.empty()) {
            path.push_back(s.top());
            s.pop();
        }
        sssp.push_back({n.vertex,n.length,path});
    }
    return sssp;
}

#ifndef NENTRY
int main()
{
    auto const & example = CLRS3::Figure_24_2;
    auto g = make_graph<DirectedWeightedGraph>(example);
    auto sssp = BellmanFord<Vertex,Weight,Edge,DirectedWeightedGraph>(g,"s");
    for (auto [v,w,p] : sssp) {
        cout << v << ": ";
        if (!p.empty()) {
            cout << setw(9) << setfill('0') << fixed << setprecision(6) << w << ": ";
        }
        for (auto u : p) cout << u << "-";
        if (!p.empty()) {
            cout << v;
        }
        cout << endl;
    }
}
#endif

