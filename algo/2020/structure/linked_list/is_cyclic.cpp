#include <iostream>

using namespace std;

template <typename data_t>
struct node
{
    using data_type = data_t;
    using node_type = node<data_type>;

    node(data_type v, node_type * n) : value(v), next(n) {}
    node(data_type v) : node(v,nullptr) {}

    data_type value;
    node_type * next;
};

template <typename data_t>
ostream & operator << (ostream & s, node<data_t> const & n)
{
    return s << "(" << n.value << ")";
}

template <typename node_t>
auto link(node_t * source, node_t * target)
{
    source->next = target;
}

template <typename node_t, typename func_t>
auto traverse(node_t * n, func_t f)
{
    while (n) {
        f(n);
        n = n->next;
    }
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
auto next(node_t * n, int i)
{
    while (n && i > 0) {
        n = n->next;
        i--;
    }
    return n;
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

int main()
{
    using node_type = node<char>;
    node_type * a = new node_type('A');
    node_type * b = new node_type('B');
    node_type * c = new node_type('C');
    node_type * d = new node_type('D');
    node_type * e = new node_type('E');
    link(a,b);
    link(b,c);
    link(c,d);
    link(d,e);
    link(e,c);
    auto list = a;
    cout << size(d) << endl;
    cout << *next(a,0) << *next(a,1) << *next(a,2) << *next(a,12) << endl;
    if (auto * x = has_cycle(a); x) cout << (*x) << endl;
}

