template <typename data_t>
struct node
{
    using date_type = data_t;
    using node_type = node<date_type>;
    using link_type = node_type *;

    node(date_type data, link_type n) : data(data), next(n) {}
    explicit node(date_type data) : node(data,nullptr) {}

    date_type data;
    link_type next;
};

template <typename data_t>
auto insert_after(node<data_t> * p, node<data_t> * n)
{
    if (p && n) {
        n->next = p->next;
        p->next = n;
    }
}

template <typename data_t>
auto delete_after(node<data_t> * p)
{
    if (auto n = p->next; n) {
        p->next = n->next;
        delete n;
    }
}

template <typename data_t>
ostream & operator << (ostream & s, node<data_t> const & n)
{
    return s << "(" << n.data << ")";
}

template <typename data_t>
ostream & operator << (ostream & s, node<data_t> const * p)
{
    for (auto const * n = p; n != nullptr; n = n->next) {
        s << (*n);
    }
    return s;
}

template <typename node_t> using list = typename node_t::link_type;


