#include "graph.h"

using namespace std;

int main(int argc, char const ** argv)
{
    string source_node = "200";
    cerr << "usage: graph_traverse soude-node(default=200) < data-file" << endl;

    if (argc > 1) {
        source_node.assign(argv[1]);
    }

    auto g = graph<node<string>,edge<string,double>>::make_graph<undirected>(cin);
    auto n = node<string>(source_node);
    auto v = [](auto const & n){ cout << n; };
    search<strategies::container<strategies::DFS>::type>(g,n,v); cout << endl;
}
