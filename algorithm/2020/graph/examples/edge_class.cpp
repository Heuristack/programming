#include "graph.h"

int main()
{
    auto g = graph<node<string>,edge<string>>::make_graph<directed>(clrs2205);
    auto n = node<string>("S");
    auto f = [](decltype(n) const & n, status::status_type s, visa<>::time_type t) {
        if (s == status::expanding) cout << "(" << n.v << "[" << t << "]";
        else cout << n.v << "[" << t << "]" << ")";
    };
    auto v = [f](auto const & n) { return f(n,n.s,n.enter); };
    DFS(g,n,v);
    cout << endl;
    cout << g;
}

