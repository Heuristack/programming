#include "GraphHelper.h"

template <typename Vertex, typename Weight, typename Edge, typename Graph>
auto Dijkstra(Graph g, Vertex s) -> vector<tuple<Vertex,Weight,vector<Vertex>>>
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

    auto order = [](Node const & u, Node const & v)->bool{
        return u.length < v.length;
    };

    map<Vertex,Node> open;
    for (auto [v,_] : g) {
        open[v] = Node{v,v};
    }
    open[s].length = 0;

    auto extract_min = [order,&open]()->Node{
        auto i = min_element(begin(open),end(open),[order](auto const & a, auto const & b)->bool{
                auto [ui,u] = a;
                auto [vi,v] = b;
                return order(u,v);
        });
        if (i == end(open)) throw length_error("open list is empty");
        auto [_,n] = *i;
        open.erase(i);
        return n;
    };

    map<Vertex,Node> closed;

    while (!open.empty()) {
        auto n = extract_min();
        auto u = n.vertex;
        closed[u] = n;

        for (auto const & e : g[u]) {
            auto v = e.target;
            auto w = e.weight;
            if (closed.find(v) == closed.end())
                relax(n,open[v],w);
        }
    }

    vector<tuple<Vertex,Weight,vector<Vertex>>> sssp;
    for (auto [_,n] : closed) {
        stack<Vertex> s;
        auto p = n.parent;
        auto v = n.vertex;
        while (p != v) {
            s.push(p);
            v = p;
            p = closed[v].parent;
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

template <typename Vertex, typename Weight, typename Edge, typename Graph>
void UniformCostSearch(Graph & g, Vertex s)
{
    if (g.find(s) == g.end()) return;

    struct Node
    {
        Vertex vertex;
        Vertex parent;
        Weight length;

        bool operator < (Node const & that) const { return length > that.length; }
    };
    map<Vertex,Node> closed;

    priority_queue<Node> open;
    open.push(Node{s,{},{}});
    while (!open.empty()) {
        auto n = open.top();
        open.pop();

        auto u = n.vertex;
        auto d = n.length;

        if (closed.find(u) != closed.end()) continue;
        for (auto const & e : g[u]) {
            auto v = e.target;
            auto w = e.weight;

            // expanding nodes are also added into open list, some may already be in open list
            if (closed.find(v) == closed.end()) {
                open.push(Node{v,u,d+w});
            }
        }
        closed[u] = n;
    }

    for (auto const & [_,n] : closed) {
        cout << n.vertex << ":" << n.length << endl;
    }
}

#ifndef NENTRY
int main()
{
    auto const & example = CLRS3::Figure_24_2;
    auto g = make_graph<DirectedWeightedGraph>(example);
    auto sssp = Dijkstra<Vertex,Weight,Edge,DirectedWeightedGraph>(g,"s");
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
    UniformCostSearch<Vertex,Weight,Edge,DirectedWeightedGraph>(g,"s");
}
#endif

