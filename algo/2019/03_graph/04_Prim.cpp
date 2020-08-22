#include "GraphHelper.h"

template <typename Vertex, typename Weight, typename Edge, typename Graph>
auto Prim(Graph & g, Vertex s) -> pair<Weight,vector<Edge>>
{
    struct Node
    {
        Vertex vertex;
        Vertex parent;
        Weight weight = numeric_limits<Weight>::max();
    };

    map<Vertex,Node> open;
    for (auto [v,_] : g) {
        open[v] = Node{v,v};
    }
    open[s].weight = 0;

    auto order = [](Node const & u, Node const & v)->bool{
        return u.weight < v.weight;
    };
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
            if (open.find(v) != open.end() && w < open[v].weight) {
                open[v].parent = u;
                open[v].weight = w;
            }
        }
    }

    Weight mw {};
    vector<Edge> st;
    for (auto [_,n] : closed) {
        st.push_back(Edge{n.parent,n.vertex,n.weight});
        mw += n.weight;
    }
    return {mw,st};
}

template <typename Vertex, typename Weight, typename Edge, typename Graph>
auto Prim(Graph & g) -> pair<Weight,vector<Edge>>
{
    Weight mw = numeric_limits<Weight>::max();
    vector<Edge> st;
    for (auto [v,_] : g) {
        auto [w,t] = Prim<Vertex,Weight,Edge,Graph>(g,v);
        if (w < mw) {
            mw = w;
            st = t;
        }
        break;
    }
    return {mw,st};
}

#ifndef NENTRY
int main()
{
    auto const & example = CLRS3::Figure_23_1;
    auto g = make_graph<UndirectedWeightedGraph>(example);
    auto [mw,st] = Prim<Vertex,Weight,Edge,UndirectedWeightedGraph>(g);
    cout << "minimum weight: " << fixed << setprecision(3) << mw << endl;
    for (auto const & e : st) {
        cout << e.source << "-" << e.target << ":" << fixed << setprecision(3) << e.weight << endl;
    }
}
#endif

