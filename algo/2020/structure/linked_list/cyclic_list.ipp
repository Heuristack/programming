template <typename node_t>
auto link(node_t * source, node_t * target)
{
    source->next = target;
}

template <typename node_t>
auto next(node_t * n, int i)
{
    while (n && i > 0) {
        n = n->next;
        i--;
    }
    return n;
}

template <typename node_t>
auto size(node_t * n)
{
    auto * p = n;
    int i = 0;
    if (p) {
        do {
            n = n->next;
            i++;
        } while (n && n != p);
    }
    return i;
}

template <typename node_t>
auto has_cycle(node_t * n) -> node_t *
{
    auto * p = n, * q = n;
    while (q && q->next) {
        p = p->next; q = q->next->next;
        if (p == q) {
            auto * i = p;
            auto * e = next(p,size(p));
            while (i != e) {
                i = i->next;
                e = e->next;
            }
            return i;
        }
    }
    return nullptr;
}

template <typename node_t, typename func_t>
auto traverse(node_t * n, func_t f)
{
    while (n) {
        f(n);
        n = n->next;
    }
}

