#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include "interval.h"

using namespace std;

bool is_open(vector<endpoint> const & endpoints)
{
    map<int,int> intervals_status;
    for (auto const & e : endpoints) {
        intervals_status[e.i] = e.m;
    }
    return any_of(begin(intervals_status),end(intervals_status),[](auto const & is){
        if (auto const & [i,s] = is; s == 0) { return true; }
        else return false;
    });
}

auto merge(vector<endpoint> & endpoints) -> interval
{
    interval i(endpoints.front().e,endpoints.back().e);
    endpoints.clear();
    return i;
}

auto merge(vector<interval> & intervals) -> vector<interval>
{
    sort(begin(intervals),end(intervals),[](auto const & a, auto const & b) {
        return a.p < b.p;
    });

    vector<endpoint> endpoints;
    for (int i = 0; i < intervals.size(); i++) {
        endpoints.emplace_back(intervals[i].p,i,0);
        endpoints.emplace_back(intervals[i].q,i,1);
    }
    sort(begin(endpoints),end(endpoints),[](auto const & a, auto const & b) {
        if (a.e == b.e) { return a.m < b.m; }
        else return a.e < b.e;
    });

    vector<interval> results;
    vector<endpoint> stack;
    for (auto e : endpoints) {
        if (e.m == 1) {
            if (auto b = stack.back(); b.i == e.i) {
                stack.pop_back();
                if (stack.empty()) {
                    results.emplace_back(b.e,e.e);
                }
                continue;
            }
        }
        stack.push_back(e);
        if (!is_open(stack)) {
            results.push_back(merge(stack));
        }
    }
    return results;
}


int main()
{
    vector<interval> intervals = {{-4,-1},{0,2},{3,6},{7,9},{11,12},{14,17},{1,8}};
    for (auto i : merge(intervals)) cout << i; cout << endl;
}

