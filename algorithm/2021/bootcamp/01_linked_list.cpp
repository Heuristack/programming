/**
 *
 * Bootcamp01: Implement a linked_list structure
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
    node(data_type d, link_type n) : data(d),next(n) {}
    explicit node(data_type d) : node(d,nullptr) {}

public:
    data_type data;
    link_type next;
};

template <typename data_t>
ostream & operator << (ostream & s, node<data_t> const & n)
{
    return s << "(" << n.data << ")";
}

template <typename data_t>
auto traverse(node<data_t> * head)
{
    for (node<int> * p = head; p != nullptr; p = p->next) {
        cout << (*p) << endl;
    }
}

int main()
{
    using node_type = node<int>;
    typename node_type::link_type head =
        new node_type(0,
            new node_type(1,
                new node_type(2,
                    new node_type(3,
                        new node_type(4)))));
    traverse(head);
}

