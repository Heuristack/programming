#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

using namespace std;

template <typename data_t>
struct node
{
    using data_type = data_t;
    using node_type = node<data_type>;

    node(data_type v, node_type * l, node_type * r) : data(v), ltree(l), rtree(r) {}
    explicit node(data_type v) : node(v,nullptr,nullptr) {}

    data_type data;
    node_type * ltree;
    node_type * rtree;
};

template <typename data_t>
ostream & operator << (ostream & strm, node<data_t> const & n)
{
    strm << "(" << n.data << ")";
    return strm;
}

template <typename node_t>
auto traverse(node_t * n) -> map<int,vector<node_t*>>
{
    static map<int,vector<node_t*>> node_map;
    static int depth = 0;
    if (n) {
        node_map[depth++].push_back(n);
        traverse(n->ltree);
        traverse(n->rtree);
        depth--;
    }
    return node_map;
}

int main()
{
    using node_type = node<int>;
    node_type * tree = new node_type(314,
            new node_type(6,
                new node_type(271,
                    new node_type(28),
                    new node_type(0)),
                new node_type(561,
                    nullptr,
                    new node_type(3,
                        new node_type(17),
                        nullptr))),
            new node_type(6,
                new node_type(2,
                    nullptr,
                    new node_type(1,
                        new node_type(401,
                            nullptr,
                            new node_type(641)),
                        new node_type(257))),
                new node_type(271,
                    nullptr,
                    new node_type(28))));

    for (auto const & [i,v] : traverse<node_type>(tree)) {
        cout << i << ":";
        for (auto const * n : v) {
            cout << (*n);
        }
        cout << endl;
    }
}

