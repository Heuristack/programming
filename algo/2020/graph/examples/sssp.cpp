#include "graph.h"

int main()
{
    auto g = graph<node<string>,edge<string,int>>::make_graph<directed>(clrs2406);
    auto n = node<string>("S");
    auto f = [](auto const & v) {
        for (auto const & [n,a] : v) {
            cout << a.v << ":" << a.p
                 << "=" << a.l << " ";
        }
        cout << endl;
    };
    f(bellman_ford(g,n));
    f(dijkstra(g,n));
}

