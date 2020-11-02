#include "explicit_graph.h"
#include "algorithm/minimum_spanning_tree.hpp"

using namespace std;

int main()
{
    auto g = graph<node<string>,edge<string,int>>::make_graph<undirected>(clrs2301);
    auto n = node<string>("S");
    int minimum_weight = 0;
    for (auto const & e : kruskal(g)) {
        minimum_weight += e.w;
        cout << e;
    }
    cout << minimum_weight << endl;
}

