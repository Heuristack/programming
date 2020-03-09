#include <iostream>

template <typename value_t>
struct node
{
    using value_type = value_t;
    using node_type = node<value_type>;
    using link_type = node_type *;

    node(value_type v, link_type n) : value(v), next(n) {}
    explicit node(value_type v) : node(v,nullptr) {}

    value_type value;
    link_type next{nullptr};
};

template <typename value_t>
using link = typename node<value_t>::link_type;

template <typename value_t>
using list = link<value_t>;

template <typename value_t>
bool is_empty(list<value_t> const & head)
{
    return head == nullptr;
}

template <typename value_t>
auto traverse(list<value_t> const & head)
{
    for (auto p = head; p != nullptr; p = p->next) {
        std::cout << p->value << std::endl;
    }
}

template <typename value_t>
auto traverse_recursive(list<value_t> const & head)
{
    if (head == nullptr) return;
    else {
        traverse_recursive<value_t>(head->next);
        std::cout << head->value << std::endl;
    }
}

int main()
{
    using node_type = node<int>;
    using list_type = list<node_type::value_type>;

    list_type head = new node_type(3, new node_type(1, new node_type(4,
            new node_type(1, new node_type(5,new node(9))))));

    traverse<node_type::value_type>(head);
    traverse_recursive<node_type::value_type>(head);
}

