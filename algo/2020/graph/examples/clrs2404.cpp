#include "graph.h"

using namespace std;

int main()
{
    auto g = graph<node<string>,edge<string,int>>::make_graph<undirected>(clrs2404);
    auto n = node<string>("S");
    auto v = [](auto const & n){ cout << n; };

    cout << "DFS(recursive) path: "; DFS(g,n,v); cout << endl;
    cout << "DFS path: "; search<strategies::container<strategies::DFS>::type>(g,n,v); cout << endl;
    cout << "BFS path: "; search<strategies::container<strategies::BFS>::type>(g,n,v); cout << endl;
}

