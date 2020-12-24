#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct record
{
    string n;
    double v;

    bool operator < (record const & that) const { return v < that.v; }
    friend ostream & operator << (ostream & s, record const & o) { return s << o.n << "," << o.v; }
};

int main()
{
    priority_queue<record> q;
    q.push(record{"c", 3.14});
    q.push(record{"a", 1.41});
    q.push(record{"b", 2.71});
    while (!q.empty()) { cout << q.top() << endl; q.pop(); }

    vector<record> v;
    v.push_back(record{"c", 3.14}); push_heap(begin(v),end(v));
    v.push_back(record{"a", 1.41}); push_heap(begin(v),end(v));
    v.push_back(record{"b", 2.71}); push_heap(begin(v),end(v));
    for (auto const & e : v) { cout << e << endl; }
    for (auto i = end(v); i != begin(v); i = prev(i)) { pop_heap(begin(v),i); }
    for (auto const & e : v) { cout << e << endl; }
}

