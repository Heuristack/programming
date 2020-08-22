#include <initializer_list>
#include <iostream>

using namespace std;

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

template <typename node_t>
using list = typename node_t::link_type;

template <typename data_t>
auto create_list(initializer_list<data_t> const & init)
{
    list<node<data_t>> head = nullptr;
    list<node<data_t>> tail = head;
    assert(!tail);
    for (auto const & data : init) {
        if (!tail) {
            tail = new node<data_t>(data);
            head = tail;
        }
        else {
            tail->next = new node<data_t>(data);
            tail = tail->next;
        }
    }
    return head;
}

template <typename list_t, typename func_t>
auto traverse(list_t const & head, func_t func)
{
    for (auto i = head; i != nullptr; i = i->next) {
        func(i->data);
    }
}

template <typename list_t, typename pred_t>
auto remove_if(list_t & head, pred_t pred)
{
    if (!head) return;
    assert(head);
    while (head && pred(head->data)) {
        auto x = head;
        head = head->next;
        delete x;
    }
    if (!head) return;
    assert(head && !pred(head->data));
    auto prev_node = head;
    auto this_node = head->next;
    while (this_node) {
        if (pred(this_node->data)) {
            prev_node->next = this_node->next;
            delete this_node;
            this_node = prev_node->next;
        }
        else {
            prev_node = this_node;
            this_node = this_node->next;
        }
    }
}

template <typename list_t>
auto delete_list(list_t & head)
{
    remove_if(head,[](auto const &){ return true; });
}

int main()
{
    auto list = create_list<int>({3,1,4,1,5,9});
    traverse(list,[](auto const & data){ cout << data; });
    cout << endl;

    remove_if(list,[](auto const & data){ return data == 1; });
    traverse(list,[](auto const & data){ cout << data; });
    cout << endl;

    delete_list(list);
    traverse(list,[](auto const & data){ cout << data; });
    cout << endl;
}

