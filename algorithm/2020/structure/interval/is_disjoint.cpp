#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

#include "interval.hpp"

using namespace std;

bool is_disjoint(vector<interval> & intervals)
{
    if (intervals.size() < 2) return true;
    sort(begin(intervals),end(intervals),[](auto const & a, auto const & b) {
        return a.p < b.p;
    });
    for (int i = 0; i < intervals.size() - 1; i++) {
        if (intervals[i].q >= intervals[i+1].p) {
            return false;
        }
    }
    return true;
}

int main()
{
    vector<interval> intervals = {{-4,-1},{0,2},{3,6},{7,9},{11,12},{14,17},{1,8}};
    for (auto i : intervals) cout << i; cout << endl;
    cout << is_disjoint(intervals) << endl;
}

