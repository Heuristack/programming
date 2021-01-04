#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

template <typename data_t = string>
struct node
{
public:
    using data_type = data_t;
    using node_type = node<data_type>;
    using link_type = node_type *;

public:
    explicit node(data_type const & data): data(data) {}
    auto link(link_type link) { if (link) adjacents.push_back(link); }

public:
    data_type data;
    vector<link_type> adjacents;
};

template <typename data_t>
ostream & operator << (ostream & s, node<data_t> const & n)
{
    return s << "(" << n.data << ")";
}

template <typename node_t, typename visitor_t>
auto search(node_t * n, visitor_t f)
{
    if (!n) return;
    vector<node_t*> close; // note : this can also be achieved by keeping status in node
    close.push_back(n);
    queue<node_t*> q;
    q.push(n);
    while (!q.empty()) {
        node_t * u = q.front();
        q.pop();
        f(u);
        for (auto v : u->adjacents) {
            if (find(begin(close),end(close),v) != end(close)) continue;
            close.push_back(v);
            q.push(v);
        }
    }
}

int main()
{
    // node : erickson0605
    node<> s("s");
    node<> t("t");
    node<> u("u");
    node<> v("v");
    node<> w("w");
    s.link(&t);
    t.link(&u);
    t.link(&v);
    u.link(&v);
    u.link(&w);
    u.link(&s);
    w.link(&v);
    search(&s,[](auto * n){ if (n) cout << (*n); });
}
