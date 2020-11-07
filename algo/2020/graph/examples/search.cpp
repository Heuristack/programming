#include "explicit_graph.h"
#include "algorithm/search.hpp"

using namespace std;

int main()
{
    auto g = graph<node<string>,edge<string>>::make_graph<directed>(clrs2205);
    auto n = node<string>("S");
    auto f = [](decltype(n) const & n, status::status_type s, visa<>::time_type t) {
        if (s == status::expanding) cout << "(" << n.v << "[" << t << "]";
        else cout << n.v << "[" << t << "]" << ")";
    };
    auto v = [f](auto const & n) { return f(n,n.s,n.enter); };

    cout << "DFS(recursive) path: "; DFS(g,n,f); cout << endl;
    cout << "DFS path: "; search<container<strategies::DFS>::type>(g,n,v); cout << endl;
    cout << "BFS path: "; search<container<strategies::BFS>::type>(g,n,v); cout << endl;
    cout << "BST path: "; search<container<strategies::BST>::type>(g,n,v); cout << endl;
}

