#include "tree.h"

class generation_tree : public tree<node<string>,edge<string>>
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
    typename generation_tree::node_type n("a");
    generation_tree g;
    auto v = [](auto const & n){ cout << n; };
    search<container<strategies::BFS>::type>(g,n,v);
}

