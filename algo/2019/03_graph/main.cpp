#define NENTRY
#include "GraphHelper.h"
#include "03_Kruskal.cpp"
#include "04_Prim.cpp"
#include "05_BellmanFord.cpp"
#include "06_Dijkstra.cpp"

int main()
{
    auto g = make_graph<UndirectedWeightedGraph>(cin);
{
    cout << "Minimum Spanning Tree" << endl;
    {
        cout << "Kruskal:" << endl;
        auto [mw,st] = Kruskarl<Vertex,Weight,Edge,UndirectedWeightedGraph>(g);
        cout << "minimum weight: " << fixed << setprecision(6) << mw << endl;
        for (auto const e : st) { cout << e.source << "," << e.target << ":" << fixed << setprecision(6) << e.weight << endl; }
        cout << endl;
    }
    {
        cout << "Prim:" << endl;
        auto [mw,st] = Prim<Vertex,Weight,Edge,UndirectedWeightedGraph>(g);
        cout << "minimum weight: " << fixed << setprecision(6) << mw << endl;
        for (auto const e : st) { cout << e.source << "," << e.target << ":" << fixed << setprecision(6) << e.weight << endl; }
        cout << endl;
    }
}
{
    cout << "Single Source Shortest Path" << endl;
    {
        cout << "BellmanFord:" << endl;
        auto sssp = BellmanFord<Vertex,Weight,Edge,UndirectedWeightedGraph>(g,"000");
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
        cout << endl;
    }
    {
        cout << "Dijkstra:" << endl;
        auto sssp = Dijkstra<Vertex,Weight,Edge,UndirectedWeightedGraph>(g,"000");
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
        cout << endl;
    }
}
}

