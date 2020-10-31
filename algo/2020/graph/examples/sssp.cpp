#include "explicit_graph.h"
#include "algorithm/single_source_shortest_path.hpp"

using namespace std;

int main()
{
    auto g = graph<node<string>,edge<string,int>>::make_graph<directed>(clrs2404);
    auto n = node<string>("S");
    auto v = bellman_ford(g,n);
    for (auto const & [n,a] : v) {
        cout << "(" << a.v << ":" << a.p << ") = " << a.l << endl;
    }
}

