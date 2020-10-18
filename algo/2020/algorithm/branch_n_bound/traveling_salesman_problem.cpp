#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

using namespace std;

constexpr auto mi = numeric_limits<int>::min();
constexpr auto mx = numeric_limits<int>::max();
constexpr auto n = 6;

vector<vector<int>> cost = {
    {mx,27,43,16,30,26},
    { 7,mx,16, 1,30,25},
    {20,13,mx,35, 5, 0},
    {21,16,25,mx,18,18},
    {12,46,27,48,mx, 5},
    {23, 5, 5, 9, 5,mx},
};
auto show(vector<vector<int>> const & cost)
{
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (cost[i][j] == mx) {
            cout << "+-,";
            continue;
        }
        cout << setw(2)
        << setfill('0')
        << cost[i][j]
        << ",";
    }   cout << endl;
    }
}

struct node
{
    vector<int> path;
    vector<int> cans = {1,2,3}; // todo
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
auto explore(node const & e) -> void
{
    show(e);
    for (auto const & n : generate(node(e))) {
        explore(n);
    }
}

int main()
{
    explore(node());
}

