/**
 *
 * Bootcamp01: Implement a linked_list structure
 *
**/

#include <iostream>
#include <vector>

using namespace std;

template <typename data_t>
class node
{
public:
    using data_type = data_t;
    using node_type = node<data_type>;
    using link_type = node_type*;

public:
    node(data_type d, link_type n) : data(d),next(n) {}
    explicit node(data_type d) : node(d,nullptr) {}

public:
    data_type data;
    link_type next;
};

template <typename data_t>
auto link(node<data_t> & a, node<data_t> & b)
{
    a.next = &b;
}

template <typename data_t>
ostream & operator << (ostream & s, node<data_t> const & n)
{
    return s << "(" << n.data << ")";
}

int main()
{
    using node_type = node<int>;

    typename node_type::link_type list =
        new node_type(0,
            new node_type(1,
                new node_type(2,
                    new node_type(3,
                        new node_type(4)))));

    for (node<int> * p = list; p != nullptr; p = p->next) {
        cout << (*p) << endl;
    }
}

