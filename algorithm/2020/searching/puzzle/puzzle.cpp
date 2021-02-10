#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <utility>
#include <iostream>
#include "board/board.h"

template <typename element = int>
class node : public board<element>
{
public:
    using board_type = board<element>;
    using board_type::board_type;

public:
    auto locate(element e = 0) const -> pair<int,int>
    {
        for (int i = 0; i < this->size_m(); i++) {
        for (int j = 0; j < this->size_n(); j++) {
            if (this->get(i,j) == e) {
                return {i,j};
            }
        }
        }
        return {0,0};
    }
    auto serialize() const -> vector<element>
    {
        vector<element> s;
        for (int i = 0; i < this->size_m(); i++) {
        for (int j = 0; j < this->size_n(); j++) {
            s.push_back(this->get(i,j));
        }
        }
        return s;
    }
};

template <typename element>
auto operator < (node<element> const & a, node<element> const & b) -> bool
{
    auto as = a.serialize(); auto bs = b.serialize();
    return lexicographical_compare(begin(as),end(as), begin(bs),end(bs));
}

template <typename element>
auto operator << (ostream & s, vector<node<element>> const & v) -> ostream &
{
    for (auto const & e : v) {
        s << e;
    }
    return s;
}

template <typename node>
class distance_function
{
public:
    static auto hamming(node const & a, node const & b) -> int
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

    static auto manhattan(node const & a, node const & b) -> int
    {
        int m = min(a.size_m(),b.size_m());
        int n = min(a.size_n(),b.size_n());
        int distance = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] == 0 || b[i][j] == 0) continue;
                auto [p,q] = a.locate(b[i][j]);
                distance += abs(p-i) + abs(q-j);
            }
        }
        return distance;
    }
};

template <typename node, typename distance_function>
class heuristic
{
public:
    heuristic(distance_function d, node i, node g, double a, double b)
    : d(d),i(std::move(i)),g(std::move(g)),a(a),b(b) {}

public:
    double operator()(node const & e) const { return a * d(i,e) + b * d(e,g); }

public:
    explicit operator bool () const { return d != nullptr; }
    distance_function d = nullptr;

public:
    double a;
    double b;

public:
    node i;
    node g;
};

template <typename node, typename distance_function>
class puzzle
{
public:
    typedef heuristic<node, distance_function> heuristic_type;
    typedef puzzle<node, distance_function> this_type;

public:
    puzzle(distance_function d, node i, node g, double a, double b)
    : h(d,i,g,a,b) {}
    auto reset() -> this_type & { path.clear(); close.clear(); return *this; }

public:
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

    auto generate(node const & n) -> vector<node>
    {
        vector<node> v;
        auto [i,j] = n.locate();
        for (auto [p,q] : generate(i,j,n.size_m(),n.size_n())) {
            node e(n);
            swap(e[i][j],e[p][q]);
            v.push_back(e);
        }
        if (!h) return v;
        sort(begin(v),end(v),[this](auto const & a, auto const & b) {
            return h(a) < h(b);
        });
        return v;
    }

public:
    auto get_track(map<node,node> & parents, node u) -> vector<node>
    {
        vector<node> v{u};
        while (parents.find(u) != parents.end()) {
            u = parents[u];
            v.push_back(u);
        }
        return v;
    }

public:
    auto explore(node const & e) -> bool
    {
        close.push_back(e);
        path.push_back(e);
        if (is_goal(e)) {
            cout << path.size();
            return 1;
        }
        for (auto const & n : generate(e)) {
            if (find(begin(close),end(close),n) != end(close))
                continue;
            if (explore(n)) return 1;
        }
        path.pop_back();
        return 0;
    }
    auto explore() -> bool { return explore(h.i); }

    auto search(node const & e) -> bool
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
                cout << "\n";
                cout << track;
                return 1;
            }
            for (auto const & v : generate(u)) {
                if (find(begin(close),end(close),v) != end(close)) {
                    continue;
                }
                open.push(v);
                parents[v] = u;
            }
        }
        return 0;
    }
    auto search() -> bool { return search(h.i); }

public:
    bool is_goal(node const & e) { return h.g == e; }

public:
    heuristic_type h;
    vector<node> path;
    vector<node> close;
};

int main()
{
    using node = node<int>;
    using dist = distance_function<node>;

    puzzle sliding(dist::manhattan,
    node{
           {4,1,2},
           {5,0,3},
    },
    node{
           {1,2,3},
           {4,5,0},
    },
    1,4);
    sliding.reset().search();
    cout << endl;

    for (int i = 1; i < 10; i++) {
        cout << i << ": ";
        puzzle sliding(dist::manhattan,
        node{
            {8,1,3},
            {4,0,2},
            {7,6,5},
        },
        node{
            {0,1,2},
            {3,4,5},
            {6,7,8},
        },
        1,i);
        sliding.reset().explore();
        cout << ":";
        sliding.reset().search();
        cout << endl;
    }
}

