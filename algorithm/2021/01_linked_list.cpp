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
    node<int> n0(0);
    node<int> n1(1); link(n0,n1);
    node<int> n2(2); link(n1,n2);
    node<int> n3(3); link(n2,n3);
    node<int> n4(4); link(n3,n4);

    node<int>::link_type list = &n0;

    for (node<int> * p = list; p != nullptr; p = p->next) {
        cout << (*p) << endl;
    }
}

