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
    explicit node(data_type d) : node(d, nullptr) {}

public:
    data_type data;
    link_type next;
};

template <typename data_t>
ostream & operator << (ostream & s, node<data_t> const & n)
{
    return s << "(" << n.data << ")";
}

int main()
{
    using node_type = node<int>;
    node_type n(10,nullptr);
    cout << n << endl;
}

