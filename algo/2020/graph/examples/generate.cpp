#include "implicit_graph.h"

class implicit_graph : public graph<node<string>,edge<string>>
{
public:
    auto operator[](node_type const & n) -> set_type<edge_type> override
    {
        static int i = 0;
        auto v = set_type<edge_type>{edge_type(n.v,n.v+n.v)};
        i++;
        if (i == 10) return {};
        return v;
    }
};

int main()
{
    typename implicit_graph::node_type n("a");
    implicit_graph g;
    auto v = [](auto const & n){ cout << n; };
    search<strategies::container<strategies::BFS>::type>(g,n,v);
}

