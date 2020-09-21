#include <iostream>
#include <limits>

using namespace std;

template <typename data_t>
struct node
{
    using data_type = data_t;
    using node_type = node<data_type>;
    using link_type = node_type *;

    node(data_type v, link_type l, link_type r) : value(v),ltree(l),rtree(r) {}
    explicit node(data_type v) : node(v,nullptr,nullptr) {}

    data_type value;
    link_type ltree;
    link_type rtree;
};

template <typename data_t>
ostream & operator << (ostream & s, node<data_t> const & n)
{
    return s << "(" << n.value << ")";
}

template <typename node_t>
auto binary_search_tree_traverse(typename node_t::link_type tree)
{
    if (!tree) return;
    binary_search_tree_traverse<node_t>(tree->ltree);
    cout << (*tree);
    binary_search_tree_traverse<node_t>(tree->rtree);
}

template <typename node_t>
auto is_binary_search_tree(typename node_t::link_type tree,
        typename node_t::data_type lower_bound,
        typename node_t::data_type upper_bound)
{
    if (!tree) return true;
    if (tree->value < lower_bound || tree->value > upper_bound) return false;
    return is_binary_search_tree<node_t>(tree->ltree, lower_bound, tree->value) &&
           is_binary_search_tree<node_t>(tree->rtree, tree->value, upper_bound);
}

template <typename node_t>
auto is_binary_search_tree(typename node_t::link_type tree)
{
    return is_binary_search_tree<node_t>(tree,
            numeric_limits<typename node_t::data_type>::min(),
            numeric_limits<typename node_t::data_type>::max());
}

int main()
{
    using node_type = node<int>;
    typename node_type::link_type tree =
        new node_type(19,
            new node_type(7,
                new node_type(3,
                    new node_type(2),
                    new node_type(5)),
                new node_type(11,
                    nullptr,
                    new node_type(17,
                        new node_type(13),
                        new node_type(20)))), // breaks BST property
            new node_type(43,
                new node_type(23,
                    nullptr,
                    new node_type(37,
                        new node_type(29,
                            nullptr,
                            new node_type(31)),
                        new node_type(41))),
                new node_type(47,
                    nullptr,
                    new node_type(53))));

    binary_search_tree_traverse<node_type>(tree);
    cout << endl;
    cout << is_binary_search_tree<node_type>(tree) << endl;
}

