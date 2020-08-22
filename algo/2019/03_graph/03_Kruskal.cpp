#include "GraphHelper.h"

template <typename Vertex, typename Weight, typename Edge, typename Graph>
auto Kruskarl(Graph & g) -> pair<Weight,vector<Edge>>
{
    map<Vertex,Vertex> dsu;
    for (auto [u,_] : g) {
        dsu[u] = u;
    }
    auto find_set = [&dsu](Vertex u)->Vertex{
        while (u != dsu[u]) {
            u = dsu[u];
        }
        return u;
    };
    auto union_set = [&dsu,&find_set](Vertex u, Vertex v){
        auto ru = find_set(u);
        auto rv = find_set(v);
        dsu[rv] = ru;
    };

    auto order = [](Edge const & a, Edge const & b)->bool{
            return a.weight < b.weight;
    };
    multiset<Edge,decltype(order)> edges(order);
    for_each_edge(g,[&edges](auto const & e){ edges.insert(e); });

    Weight mw = {};
    vector<Edge> st;
    for (auto const & e : edges) {
        auto [u,v,w] = e;
        if (find_set(u) != find_set(v)) {
            st.push_back(e);
            union_set(u,v);
            mw += w;
        }
    }

    return {mw,st};
}

#ifndef NENTRY
int main()
{
    auto const & example = CLRS3::Figure_23_1;
    auto g = make_graph<UndirectedWeightedGraph>(example);
    auto [mw,st] = Kruskarl<Vertex,Weight,Edge,UndirectedWeightedGraph>(g);
    cout << "minimum weight: " << fixed << setprecision(3) << mw << endl;
    for (auto const & e : st) {
        cout << e.source << "-" << e.target << ":" << fixed << setprecision(3) << e.weight << endl;
    }
}
#endif

