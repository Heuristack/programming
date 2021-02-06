#include <algorithm>
#include <vector>
#include <iostream>
#include "interval.h"

using namespace std;

int main()
{
    vector<interval> intervals = {{-4,-1},{0,2},{3,6},{7,9},{11,12},{14,17},{1,8}};
    for (auto i : intervals) cout << i; cout << endl;
    sort(begin(intervals),end(intervals),[](auto const & a, auto const & b) {
        return a.p < b.p;
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
    vector<endpoint> stack;
    for (auto e : endpoints) {
        if (e.m == 0) {
            stack.push_back(e);
        }
        else {
            if (stack.back().i == e.i) {
                stack.pop_back();
                results.push_back(intervals[e.i]);
            }
        }
    }
    for (auto e : stack) cout << e; cout << endl;
    for (auto i : results) cout << i; cout << endl;
}

