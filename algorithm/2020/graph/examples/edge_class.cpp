#include "graph.h"

int main()
{
    auto g = graph<node<string>,edge<string>>::make_graph<directed>(clrs2205);
    auto n = node<string>("S");
    auto v = [](auto const & n) {};
    search<container<strategies::DFS>::type>(g,n,v);
}

