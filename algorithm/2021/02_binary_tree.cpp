/**
 *
 * Bootcamp02: Implement a binary tree structure
 *
**/
#include <iostream>
using namespace std;

template <typename data_t>
class node
{
public:
    using data_type = data_t;
    using node_type = node<data_type>;
    using link_type = node_type*;
public:
    node(data_type v, link_type l, link_type r) : value(v),ltree(l),rtree(r) {}
    explicit node(data_type v) : node(v,nullptr,nullptr) {}

public:
    data_type value;
    link_type ltree;
    link_type rtree;
};

template <typename data_t>
ostream & operator << (ostream & s, node<data_t> const & n)
{
    return s << "(" << n.value << ")";
}

template <typename data_t>
auto traverse(node<data_t> * tree)
{
    if (!tree) return;
    cout << (*tree) << endl;
    traverse(tree->ltree);
    traverse(tree->rtree);
}

int main()
{
    using node_type = node<int>;
    typename node_type::link_type tree =
    new node_type(0,
        new node_type(1,
            new node_type(3),
            new node_type(4)
        ),
        new node_type(2,
            new node_type(5),
            new node_type(6)
        )
    );
    traverse(tree);
}

