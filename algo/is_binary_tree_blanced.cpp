#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

template <typename data_t>
struct node
{
    using data_type = data_t;
    using node_type = node<data_type>;

    node(data_type v, node_type * l, node_type *r) : v(v), ltree(l), rtree(r) {}
    node(data_type v) : node(v,nullptr,nullptr) {}

    data_type v;
    node_type * ltree;
    node_type * rtree;
};

template <typename data_t>
ostream & operator << (ostream & s, node<data_t> const & n)
{
    return s << "(" << n.v << ")";
}

// note : return -1 if unblanced else height of the tree
//        empty node has zero height, single node has 1 height, ...
template<typename node_t>
auto is_balanced(node_t * tree)
{
    if (!tree) return 0;
    auto l = is_balanced<node_t>(tree->ltree);
    auto r = is_balanced<node_t>(tree->rtree);
    cout << (*tree) << ":" << l << "," << r << endl;
    if (l < 0 || r < 0 || abs(l-r) > 1) return -1;
    else return max(l,r) + 1;
}

int main()
{
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
        cout << is_balanced<node_type>(tree) << endl;
    }
    {
        using node_type = node<char>;
        node_type * tree = new node_type('A',
                new node_type('B',
                    new node_type('C',
                        new node_type('D',
                            new node_type('E'),
                            new node_type('F')),
                        new node_type('G')),
                    new node_type('H',
                        new node_type('I'),
                        new node_type('J'))),
                new node_type('K',
                    new node_type('L',
                        new node_type('M'),
                        new node_type('N')),
                    new node_type('O')));
        cout << is_balanced<node_type>(tree) << endl;
    }
}

