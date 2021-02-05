#include <algorithm>
#include <vector>
#include <stack>
#include <cassert>
#include <ostream>
#include <iostream>

using namespace std;

struct interval
{
    interval(int p, int q): p(p),q(q) { assert(p < q); }
    int p,q;
};

ostream & operator << (ostream & s, interval const & i)
{
    return s << "(" << i.p << "," << i.q << ")";
}

bool is_disjoint(vector<interval> const & intervals)
{
    if (intervals.size() < 2) return 1;
    for (int i = 0; i < intervals.size() - 1; i++) {
        if (intervals[i].q >= intervals[i+1].p) {
            return 0;
        }
    }
    return 1;
}

struct endpoint
{
    endpoint(int e, int i, int b): e(e),i(i),b(b) {}
    int e,i,b;
};

ostream & operator << (ostream & s, endpoint const & e)
{
    return s << "(" << e.e << "," << e.i << "," << e.b << ")";
}

int main()
{
    vector<interval> intervals = {{-4,-1},{0,2},{3,6},{7,9},{11,12},{14,17},{1,8}};
    for (auto i : intervals) cout << i; cout << endl;
    sort(begin(intervals),end(intervals),[](auto const & a, auto const & b) {
        return a.q < b.q;
    });
    for (auto i : intervals) cout << i; cout << endl;
    vector<endpoint> endpoints;
    for (int i = 0; i < intervals.size(); i++) {
        endpoints.emplace_back(intervals[i].p,i,0);
        endpoints.emplace_back(intervals[i].q,i,1);
    }
    sort(begin(endpoints),end(endpoints),[](auto const & a, auto const & b) {
        return a.e < b.e;
    });
    for (auto e : endpoints) cout << e; cout << endl;

    vector<interval> results;
    vector<endpoint> s;
    for (auto e : endpoints) {
        if (e.b == 0) {
            s.push_back(e);
        }
        else {
            if (s.back().i == e.i) {
                s.pop_back();
                results.push_back(intervals[e.i]);
            }
        }
    }
    for (auto e : s) cout << e; cout << endl;
    for (auto i : results) cout << i; cout << endl;
}

