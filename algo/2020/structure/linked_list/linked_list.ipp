template <typename data_t>
auto create_list(initializer_list<data_t> const & init) -> list<node<data_t>>
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

template <typename list_t, typename pred_t>
auto remove_if(list_t & head, pred_t pred) -> void
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
auto delete_list(list_t & head) -> void
{
    remove_if(head,[](auto const &){ return true; });
}

template <typename list_t, typename func_t>
auto traverse(list_t const & head, func_t func) -> void
{
    for (auto i = head; i != nullptr; i = i->next) {
        func(i->data);
    }
}

