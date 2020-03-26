#include <iostream>
#include <vector>
#include <queue>

using namespace std;

auto merge_n(vector<vector<int>> a) -> vector<int>
{
    vector<int> m;
    struct index
    {
        using iterator = vector<int>::iterator;
        index(iterator c, iterator e) : current(c), end(e) {}
        iterator current;
        iterator end;
        bool operator < (index const & that) const { return *current > *that.current; }
    };
    priority_queue<index> pq;
    for (auto v : a) {
        if (!v.empty()) {
            pq.emplace(begin(v),end(v));
        }
    }
    while (!pq.empty()) {
        auto i = pq.top();
        pq.pop();
        if (i.current != i.end) {
            m.emplace_back(*i.current);
            pq.emplace(next(i.current),i.end);
        }
    }
    return m;
}

int main()
{
    vector<vector<int>> a {{3,5,7},{0,6},{0,6,28}};
    for (auto i : merge_n(a)) cout << "(" << i << ")";
    cout << endl;
}

