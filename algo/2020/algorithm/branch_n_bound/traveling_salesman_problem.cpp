#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

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
        reduced += min;
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
        reduced += min;
    }
    return reduced;
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
    explore(node({1},{2,3,4,5,6}));
    show(min_cost_path);
    cout << " = ";
    cout << min_cost << endl;
    show(cm);
    cout << reduce(cm) << endl;
    show(cm);
}

