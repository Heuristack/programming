#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <initializer_list>
#include <variant>
#include <functional>

using namespace std;

ostream & operator << (ostream & o, vector<string> const & v)
{
    for (auto const & e : v) o << e;
    return o;
}

#include "structure/node.hpp"
#include "structure/edge.hpp"
#include "structure/container.hpp"
#include "algorithm/search.hpp"

#include "stream/node.hpp"

class graph
{
public:
    typedef node<string> node_type;
    typedef edge<string> edge_type;

public:
    auto generate(node_type const & n) -> vector<edge_type>
    {
       static int i = 0;
       auto v = vector<edge_type>{edge_type(n.v,n.v+n.v)};
       i++;
       if (i == 10) return {};
       return v;
    }

    auto operator[](node_type const & n)
    {
        return generate(n);
    }

    bool contains(node_type const & n) const { return true; }
};

int main()
{
    node<string> n("a");
    graph g;
    auto v = [](auto const & n){ cout << n; };
    search<strategies::container<strategies::BFS>::type>(g,n,v);
}
