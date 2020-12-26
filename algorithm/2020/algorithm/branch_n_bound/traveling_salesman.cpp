#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <set>
#include <limits>
#include <utility>
#include <tuple>
#include <algorithm>

using namespace std;

constexpr auto mi = numeric_limits<int>::min();
constexpr auto mx = numeric_limits<int>::max();
constexpr auto n = 6;

vector<vector<int>> cm = {
        {mx,27,43,16,30,26},
        { 7,mx,16, 1,30,25},
        {20,13,mx,35, 5, 0},
        {21,16,25,mx,18,18},
        {12,46,27,48,mx, 5},
        {23, 5, 5, 9, 5,mx},
};

auto show(vector<vector<int>> const & matrix)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == mx) {
                cout << "+*,";
                continue;
            }
            if (matrix[i][j] == mi) {
                cout << "-*,";
                continue;
            }
            cout << setw(2)
                 << setfill('0')
                 << matrix[i][j]
                 << ",";
        }   cout << endl;
    }
}

auto make(vector<vector<int>> const & m)
{
    return vector<vector<int>>(m);
}

auto exclude(vector<vector<int>> & m, int i, int j) -> vector<vector<int>> &
{
    m[i][j] = mx;
    return m;
}

auto include(vector<vector<int>> & m, int i, int j) -> vector<vector<int>> &
{
    for (int k = 0; k < n; k++) {
        m[i][k] = mx;
        m[k][j] = mx;
    }
    return m;
}

auto reduce(vector<vector<int>> & matrix) -> int
{
    int reduced = 0;
    for (int i = 0; i < n; i++) {
        int min = mx;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != mx) {
                matrix[i][j] -= min;
            }
        }
        if (min != mx) {
            reduced += min;
        }
    }
    for (int j = 0; j < n; j++) {
        int min = mx;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] != mx) {
                matrix[i][j] -= min;
            }
        }
        if (min != mx) {
            reduced += min;
        }
    }
    return reduced;
}

auto theta(vector<vector<int>> const & m, int i, int j) -> int
{
    int min, tht = 0;
    min = mx;
    for (int k = 0; k < n; k++) {
        if (k == j) continue;
        if ((m[i][k] != mx) && (m[i][k] < min)) {
            min = m[i][k];
        }
    }
    if (min != mx) {
        tht += min;
    }
    min = mx;
    for (int k = 0; k < n; k++) {
        if (k == i) continue;
        if ((m[k][j] != mx) && (m[k][j] < min)) {
            min = m[k][j];
        }
    }
    if (min != mx) {
        tht += min;
    }
    return tht;
}

auto theta(vector<vector<int>> const & m) -> vector<vector<int>>
{
    vector<vector<int>> t(n,vector<int>(n,0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t[i][j] = theta(m,i,j);
        }
    }
    return t;
}

auto zero(vector<vector<int>> const & m) -> bool
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (m[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

auto max_element(vector<vector<int>> const & m) -> pair<int,int>
{
    int max = mi;
    int mxi = -1;
    int mxj = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((m[i][j] != mx) && (m[i][j] > max)) {
                max = m[i][j];
                mxi = i;
                mxj = j;
            }
        }
    }
    return {mxi,mxj};
}

auto cans(vector<vector<int>> const & m) -> vector<pair<int,int>>
{
    vector<pair<int,int>> c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (m[i][j] != mx) {
                c.emplace_back(i,j);
            }
        }
    }
    return c;
}

struct node {
    node(vector<vector<int>> const &m) : matrix(m) { bound = reduce(matrix); }

    vector<pair<int, int>> path;
    vector<vector<int>> matrix;
    int bound;
};

auto next(vector<pair<int, int>> const &path, int s) -> int {
    for (auto[i, j] : path) {
        if (i == s) {
            return j;
        }
    }
    return -1;
}

auto show_path(vector<pair<int, int>> const &p) -> void {
    int s = 0;
    cout << "(" << s + 1;
    for (int i = next(p, 0); i > 0; i = next(p, i)) {
        cout << i + 1;
    }
    cout << ")";
}

auto show(vector<pair<int, int>> const &p) -> void {
    for (auto[i, j] : p) {
        cout << "(" << i << "," << j << ")";
    }
}

auto show(node const &e) -> void {
    cout << "[";
    show(e.path);
    cout << "]" << endl;
    show(e.matrix);
    cout << e.bound << endl;
}

auto exclude(node const &e, int i, int j) -> node {
    node x(e);
    exclude(x.matrix, i, j);
    x.bound += reduce(x.matrix);
    return x;
}

auto include(node const &e, int i, int j) -> node {
    node x(e);
    include(x.matrix, i, j);
    for (auto[m, p] : e.path) {
        if (p == i) {
            exclude(x.matrix, j, m);
        }
        if (j == m) {
            exclude(x.matrix, p, i);
        }
    }
    exclude(x.matrix, j, i);
    x.path.emplace_back(i, j);
    x.bound += reduce(x.matrix);
    return x;
}

auto choose(node const &e) -> pair<int, int> {
    int i = 0, j = 0;
    if (auto t = theta(e.matrix); !zero(t)) {
        tie(i, j) = max_element(t);
    } else {
        tie(i, j) = cans(e.matrix).back();
    }
    return {i, j};
}

auto explore(node const &e) -> node {
    if (e.path.size() == n) {
        return e;
    }
    auto[i, j] = choose(e);
    auto a = exclude(e, i, j);
    auto b = include(e, i, j);
    if (a.bound < b.bound) return explore(a);
    else return explore(b);
}

// An algorithm for the traveling salesman problem.
// Little, J.D., Murty, K.G., Sweeney, D.W. and Karel, C., 1963.
// Operations research, 11(6), pp.972-989.

namespace csp {

struct node
{
    node(vector<int> p, vector<int> c): path(p),cans(c) {}
    node() = default;
    vector<int> path;
    vector<int> cans;
};

auto show(vector<int> const & v) -> void
{
    cout << "(";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
    }
    cout << ")";
}

auto show(node const & n) -> void
{
    show(n.path);
    show(n.cans);
    cout << endl;
}

auto cost(vector<int> path, vector<vector<int>> const & cm) -> int
{
    path.push_back(1);
    int path_cost = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        path_cost += cm[path[i]-1][path[i+1]-1];
    }
    return path_cost;
}

auto generate(node const & e) -> vector<node>
{
    vector<node> v;
    for (auto i = begin(e.cans); i != end(e.cans); i++) {
        node n(e);
        n.path.push_back(*i);
        n.cans.erase(next(begin(n.cans),distance(begin(e.cans),i)));
        v.push_back(n);
    }
    return v;
}

auto explore(node const & e) -> vector<int> const &
{
    static vector<int> min_cost_path;
    static int min_cost = mx;

    if (e.cans.empty()) {
        if (auto path_cost = cost(e.path,cm); path_cost < min_cost) {
            min_cost = path_cost;
            min_cost_path = e.path;
        }
    }
    for (auto const & n : generate(node(e))) {
        explore(n);
    }
    return min_cost_path;
}

}

int main()
{
    // branch-bound
    auto e = explore(node(cm));
    show(e);
    show_path(e.path);
    cout << endl;

    // brute-force
    auto const & min_cost_path = csp::explore(csp::node({1},{2,3,4,5,6}));
    csp::show(min_cost_path);
    cout << " = ";
    cout << csp::cost(min_cost_path,cm) << endl;

}

