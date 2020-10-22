#include <iostream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

#include "board.hpp"

class node : public board<int>
{
public:
    typedef board<int> base_type;
public:
    node(int n): base_type(n) {}
};

auto make(vector<vector<int>> m) -> node
{
    node b(m.size());
    for (int i = 0; i < b.n; i++) {
    for (int j = 0; j < b.n; j++) {
        b[i][j] = m[i][j];
    }
    }
    return b;
}

auto is_goal(node const & e) -> bool
{
    static auto goal = make({
        {0,1,2},
        {3,4,5},
        {6,7,8},
    });
    return (e == goal);
}

auto locate(node const & b, int x = 0) -> pair<int,int>
{
    for (int i = 0; i < b.n; i++) {
    for (int j = 0; j < b.n; j++) {
        if (b[i][j] == x) {
            return {i,j};
        }
    }
    }
    return {0,0};
}

auto generate(int i, int j, int n) -> vector<pair<int,int>>
{
    vector<pair<int,int>> v;
    for (auto [p,q] : vector<pair<int,int>>{{i-1,j},{i+1,j},{i,j-1},{i,j+1}}) {
        if ((0 <= p) && (p < n) && (0 <= q) && (q < n)) {
            v.emplace_back(p,q);
        }
    }
    return v;
}

auto generate(node const & b) -> vector<node>
{
    vector<node> v;
    auto [i,j] = locate(b);
    for (auto [p,q] : generate(i,j,b.n)) {
        node n(b);
        swap(n[i][j],n[p][q]);
        v.push_back(n);
    }
    return v;
}

auto show(vector<node> const & path)
{
    for (auto const & e : path) {
        cout << e;
        cout << "->" << endl;
    }
}

auto explore(node const & e) -> bool
{
    cout << e;
    static vector<node> path = {e};
    static vector<node> c;
    c.push_back(e);
    if (is_goal(e)) {
        show(path);
        return 1;
    }
    for (auto const & n : generate(e)) {
        if (find(begin(c),end(c),n) != end(c))
            continue;
        path.push_back(n);
        if (explore(n)) return 1;
        path.pop_back();
    }
    return 0;
}

int main()
{
    auto puzzle = make({
        {8,1,3},
        {4,0,2},
        {7,6,5},
    });
    explore(puzzle);
}

