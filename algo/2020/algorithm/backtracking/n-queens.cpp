#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename element_t = int>
class board : public vector<vector<element_t>>
{
public:
    typedef vector<element_t> vector_type;
    typedef vector<vector_type> base_type;

public:
    board(int m, int n) :
        base_type(m,vector_type(n)),
        m(m),n(n) {}

    board(int n) : board(n,n) {}

public:
    int m;
    int n;
};

template <typename element_t = int>
ostream & operator << (ostream & s, board<element_t> const & b)
{
    for (int i = 0; i < b.m; i++) {
    for (int j = 0; j < b.n; j++) {
        s << b[i][j];
    }   s << "\n";
    }
    return s;
}

template <typename element_t = int>
auto is_diag_ok(board<element_t> const & b)
{}

class queen
{
public:
    int i = -1;
    int j = -1;
};

ostream & operator << (ostream & s, queen const & q) { return s << "(" << q.i << "," << q.j << ")"; }

class node
{
public:
    node(int n);

public:
    int n;
    board<int> b;
    vector<queen> q;
    vector<int> c;
};

node::node(int n):n(n),q(n),c(n),b(n)
{
    for (int i = 0; i < n; i++) {
        q[i].i = i;
        c[i] = i;
    }
}

ostream & operator << (ostream & s, node const & e)
{
    for (auto q : e.q) s << q; s << "\n";
    for (auto c : e.c) s << c; s << "\n";
    s << e.b;
    return s;
}

auto generate(node const & e)
{
    vector<node> v;
    for (int i = 0; i < e.c.size(); i++) {
        node n(e);
        auto & q = n.q[e.n - e.c.size()];
        q.j = e.c[i];
        n.c.erase(begin(n.c)+i);
        n.b[q.i][q.j] = 1;
        v.push_back(n);

    }
    return v;
}

auto explore(node const & e) -> int
{
    static int n = 0;
    if (e.c.size() == 0) {
        n++;
    }
    for (auto const & n: generate(e)) {
        explore(n);
    }
    return n;
}

int main()
{
    cout << explore(node(8));
    cout << endl;
}

