#include "graph.h"

int main()
{
    auto g = graph<node<string>,edge<string>>::make_graph<directed>(erickson0605);
    auto n = node<string>("s");
    auto f = [](decltype(n) const & n, status::status_type s, visa<>::time_type enter, visa<>::time_type leave) {
        if (s == status::expanding) cout << "(" << n.v << "[" << enter << "]";
        else cout << n.v << "[" << leave << "]" << ")";
    };
    auto v = [f](auto const & n) { return f(n,n.s,n.enter,n.leave); };
    DFS(g,n,v);
    cout << endl;
    cout << g;
}

