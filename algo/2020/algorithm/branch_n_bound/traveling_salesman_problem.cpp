#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <utility>

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
            cout << "+-,";
            continue;
        }
        cout << setw(2)
        << setfill('0')
        << matrix[i][j]
        << ",";
    }   cout << endl;
    }
}
auto cost(vector<int> path) -> int
{
    path.push_back(1);
    int path_cost = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        path_cost += cm[path[i]-1][path[i+1]-1];
    }
    return path_cost;
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
auto theta(vector<vector<int>> const & m, int i, int j) -> int
{
    int min, tht = 0;
    min = mx;
    for (int k = 0; k < n; k++) {
        if (k == j) continue;
        if (m[i][k] < min) {
            min = m[i][k];
        }
    }
    tht += min;
    min = mx;
    for (int k = 0; k < n; k++) {
        if (k == i) continue;
        if (m[k][j] < min) {
            min = m[k][j];
        }
    }
    tht += min;
    return tht;
}
auto theta_matrix(vector<vector<int>> const & m) -> vector<vector<int>>
{
    vector<vector<int>> t(n,vector<int>(n,0));
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        t[i][j] = theta(m,i,j);
    }
    }
    return t;
}
auto maximum(vector<vector<int>> const & m) -> pair<int,int>
{
    int max_i = 0;
    int max_j = 0;
    int max = mi;
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (m[i][j] > max) {
            max = m[i][j];
            max_i = i;
            max_j = j;
        }
    }
    }
    return {max_i,max_j};
}

struct node
{
    node(vector<int> p, vector<int> c): path(p),cans(c) {}
    node() = default;
    vector<int> path;
    vector<int> cans;
};
auto show(vector<int> const & v)
{
    cout << "(";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
//      if (i < v.size() - 1) {
//          cout << ",";
//      }
    }
    cout << ")";
}
auto show(node const & n)
{
    show(n.path);
    show(n.cans);
    cout << endl;
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

vector<int> min_cost_path;
int min_cost = mx;

auto explore(node const & e) -> void
{
    if (e.cans.empty()) {
        if (auto path_cost = cost(e.path); path_cost < min_cost) {
            min_cost = path_cost;
            min_cost_path = e.path;
        }
    }
    for (auto const & n : generate(node(e))) {
        explore(n);
    }
}

int main()
{
    // brute-force
    explore(node({1},{2,3,4,5,6}));
    show(min_cost_path);
    cout << " = ";
    cout << min_cost << endl;

    // branch-bound
    show(cm);
    cout << reduce(cm) << endl;
    show(cm);

    cout << "theta matrix" << endl;
    auto tm = theta_matrix(cm);
    show(tm);
    auto [i,j] = maximum(tm);
    cout << "(" << i+1 << "," << j+1 << ")" << endl;

    cout << "exclude" << endl;
    auto am = make(cm);
    exclude(am,1-1,4-1);
    show(am);
    cout << reduce(am) << endl;
    show(am);

    cout << "include" << endl;
    auto bm = make(cm);
    include(bm,1-1,4-1);
    cout << reduce(bm) << endl;
    exclude(bm,4-1,1-1);
    show(bm);
    cout << reduce(bm) << endl;
    show(bm);

    cout << "exclude" << endl;
    auto dm = make(bm);
    exclude(dm,2-1,1-1);
    show(dm);
    cout << reduce(dm) << endl;
    show(dm);
}

