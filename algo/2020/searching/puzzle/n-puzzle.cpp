#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <utility>
#include <iostream>

using namespace std;

template <typename element, typename vector_base = vector<element>, typename board_base = vector<vector_base>>
class board : public board_base
{
public:
    using board_base::board_base;
    board(int m, int n) : board_base(m,vector_base(n)) {}
    board(int n) : board(n,n) {}

public:

public:
    int size_m(int i = 0) const { return this->size(); }
    int size_n(int i = 0) const { return this->operator[](i).size(); }
};

template <typename element>
ostream & operator << (ostream & s, board<element> const & b)
{
    for (int i = 0; i < b.size_m(i); i++) {
    for (int j = 0; j < b.size_n(i); j++) {
        s << b[i][j];
    }   s << "\n";
    }
    return s;
}

class node : public board<int>
{
public:
    using board_type = board<int>;
    using board_type::board_type;
};

ostream & operator << (ostream & s, vector<node> const & v)
{
    for (auto const & e : v) {
        s << e;
    }
    return s;
}

auto make(vector<vector<int>> m) -> node
{
    node n((int)m.size());
    for (int i = 0; i < n.size_m(); i++) {
    for (int j = 0; j < n.size_n(); j++) {
        n[i][j] = m[i][j];
    }
    }
    return n;
}

auto locate(node const & n, int e = 0) -> pair<int,int>
{
    for (int i = 0; i < n.size_m(); i++) {
    for (int j = 0; j < n.size_n(); j++) {
        if (n[i][j] == e) {
            return {i,j};
        }
    }
    }
    return {0,0};
}

auto serialize(node const & n) -> vector<int>
{
    vector<int> v;
    for (int i = 0; i < n.size_m(); i++) {
    for (int j = 0; j < n.size_n(); j++) {
        v.push_back(n[i][j]);
    }
    }
    return v;
}

bool operator < (node const & a, node const & b)
{
    auto va = serialize(a);
    auto vb = serialize(b);
    return lexicographical_compare(
        begin(va),end(va),
        begin(vb),end(vb)
    );
}

template <typename distance>
class heuristic
{
public:
    heuristic(distance d, node i, node g, double a, double b)
    : d(d),i(i),g(g),a(a),b(b) {}

public:
    double operator()(node const & e) const { return a * d(e,i) + b * d(e,g); }
    operator bool () const { return d != nullptr; }

public:
    distance d = nullptr;
    node i;
    node g;
    double a;
    double b;
};

auto hamming(node const & a, node const & b) -> int
{
    int m = min(a.size_m(),b.size_m());
    int n = min(a.size_n(),b.size_n());
    int distance = 0;
    for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
        if (a[i][j] == 0 || b[i][j] == 0) continue;
        if (a[i][j] != b[i][j]) {
            distance++;
        }
    }
    }
    return distance;
}

auto manhattan(node const & a, node const & b) -> int
{
    int m = min(a.size_m(),b.size_m());
    int n = min(a.size_n(),b.size_n());
    int distance = 0;
    for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
        if (a[i][j] == 0 || b[i][j] == 0) continue;
        auto [p,q] = locate(a,b[i][j]);
        distance += abs(p-i) + abs(q-j);
    }
    }
    return distance;
}

auto generate(int i, int j, int m, int n) -> vector<pair<int,int>>
{
    vector<pair<int,int>> v;
    for (auto [p,q] : vector<pair<int,int>>{{i-1,j},{i+1,j},{i,j-1},{i,j+1}}) {
        if ((0 <= p) && (p < m) && (0 <= q) && (q < n)) {
            v.emplace_back(p,q);
        }
    }
    return v;
}

template <typename heuristic>
auto generate(node const & n, heuristic h) -> vector<node>
{
    vector<node> v;
    auto [i,j] = locate(n);
    for (auto [p,q] : generate(i,j,n.size_m(),n.size_n())) {
        node e(n);
        swap(e[i][j],e[p][q]);
        v.push_back(e);
    }
    if (!h) return v;
    sort(begin(v),end(v),[h](auto const & a, auto const & b) {
        return h(a) < h(b);
    });
    return v;
}

template <typename distance>
class puzzle
{
public:
    typedef puzzle<distance> this_type;
    typedef heuristic<distance> heuristic_type;
public:
    puzzle(distance d, node i, node g, double a, double b)
    : h(d,i,g,a,b) {}
    auto reset() -> this_type & { path.clear(); close.clear(); return *this; }

public:
    auto explore() -> bool { return explore(h.i); }
    auto explore(node const & e) -> bool;
    auto search() -> bool { return search(h.i); }
    auto search(node const & e) -> bool;

public:
    bool is_goal(node const & e) { return h.g == e; }

public:
    heuristic_type h;
    vector<node> path;
    vector<node> close;
};

template <typename distance>
auto puzzle<distance>::explore(node const & e) -> bool
{
    close.push_back(e);
    path.push_back(e);
    if (is_goal(e)) {
        cout << path.size();
        return 1;
    }
    for (auto const & n : generate(e,h)) {
        if (find(begin(close),end(close),n) != end(close))
            continue;
        if (explore(n)) return 1;
    }
    path.pop_back();
    return 0;
}

auto get_track(map<node,node> & parents, node u) -> vector<node>
{
    vector<node> v{u};
    while (parents.find(u) != parents.end()) {
        u = parents[u];
        v.push_back(u);
    }
    return v;
}

template <typename distance>
auto puzzle<distance>::search(node const & e) -> bool
{
    auto compare = [this](node const & a, node const & b) -> bool
    {
        return h(a) > h(b);
    };
    priority_queue<node,vector<node>,decltype(compare)> open(compare);
    open.push(e);
    map<node,node> parents;
    while (!open.empty()) {
        auto u = open.top();
        open.pop();
        close.push_back(u);
        if (is_goal(u)) {
            auto track = get_track(parents,u);
            cout << close.size();
            cout << ":";
            cout << track.size();
            return 1;
        }
        for (auto const & v : generate(u,h)) {
            if (find(begin(close),end(close),v) != end(close)) {
                continue;
            }
            open.push(v);
            parents[v] = u;
        }
    }
    return 0;
}

int main()
{
    for (int i = 1; i < 10; i++) {
        cout << i << ": ";
        puzzle sliding(manhattan,
        make({
            {8,1,3},
            {4,0,2},
            {7,6,5},
        }),
        make({
            {0,1,2},
            {3,4,5},
            {6,7,8},
        }),
        1,i);
        sliding.reset().explore();
        cout << ":";
        sliding.reset().search();
        cout << endl;
    }
}

