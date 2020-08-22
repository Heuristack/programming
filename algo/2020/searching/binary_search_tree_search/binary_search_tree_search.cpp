#include <iostream>

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

template <typename node_t>
auto binary_search_tree_search(typename node_t::link_type tree, typename node_t::data_type v) -> typename node_t::link_type
{
    if (!tree) return nullptr;
    else if (v < tree->value) return binary_search_tree_search<node_t>(tree->ltree,v);
    else if (v > tree->value) return binary_search_tree_search<node_t>(tree->rtree,v);
    else return tree;
}

int main()
{
    using node_type = node<int>;
    typename node_type::link_type tree = new node_type(42, new node_type(21), new node_type(65));
    auto n = binary_search_tree_search<node_type>(tree,21);
    if (n) {
        cout << n->value << endl;
    }
}

