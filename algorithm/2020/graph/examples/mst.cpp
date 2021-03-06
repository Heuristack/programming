#include "graph.h"

int main()
{
    auto g = graph<node<string>,edge<string,int>>::make_graph<undirected>(clrs2301);
    auto n = node<string>("S");
    auto f = [](auto const & v){
        int minimum_weight = 0;
        for (auto const & e : v) {
            minimum_weight += e.w;
            cout << e;
        }
        cout << ": " << minimum_weight << endl;
    };
    f(kruskal(g));
    f(prim(g));
}

