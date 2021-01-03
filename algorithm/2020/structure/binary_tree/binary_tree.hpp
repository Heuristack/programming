template <typename data_t>
class node
{
public:
    using data_type = data_t;
    using node_type = node<data_type>;
    using link_type = node_type *;

public:
    node(data_type v, link_type l, link_type r)
    : value(v),ltree(l),rtree(r) {}

    explicit node(data_type v)
    : node(v,nullptr,nullptr) {}

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

