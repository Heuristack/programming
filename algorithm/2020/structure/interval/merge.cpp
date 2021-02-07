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
    auto const & p = endpoints.front();
    auto const & q = endpoints.back();
    interval i(p.e,q.e,p.o,q.o);
    endpoints.clear();
    return i;
}

auto merge(vector<interval> & intervals) -> vector<interval>
{
    sort(begin(intervals),end(intervals),[](auto const & a, auto const & b) {
        return a.p < b.p;
    });

    vector<endpoint> endpoints;
    for (auto i = begin(intervals); i != end(intervals); i++) {
        endpoints.emplace_back(i->p,distance(begin(intervals),i),0,i->op);
        endpoints.emplace_back(i->q,distance(begin(intervals),i),1,i->oq);
    }
    sort(begin(endpoints),end(endpoints),[](endpoint const & a, endpoint const & b) {
        if (a.e == b.e) {
            if (!(a.o && b.o)) {
                if (a.m != b.m) {
                    return a.m < b.m;
                }
                else {
                    if (a.m == 0) return a.o < b.o;
                    else return a.o > b.o;
                }
            }
            else return a.i < b.i;
        }
        else return a.e < b.e;
    });

    vector<interval> results;
    vector<endpoint> stack;
    for (auto e : endpoints) {
        if (e.m == 1) {
            if (auto b = stack.back(); b.i == e.i) {
                stack.pop_back();
                if (stack.empty()) {
                    results.emplace_back(b.e,e.e,b.o,e.o);
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

int merge_test()
{
    vector<interval> intervals = {{-4,-1},{0,2},{3,6},{7,9},{11,12},{14,17},{1,8}};
    for (auto i : merge(intervals)) cout << i; cout << endl;
    return 0;
}

int union_test()
{
    vector<interval> intervals = {{0,3,1,1},{1,1,0,0},{2,4,0,0},{3,4,0,1},{5,7,0,1},{7,8,0,1},
            {8,11,0,1},{9,11,1,0},{12,14,0,0},{12,16,1,0},{13,15,1,1},{16,17,1,1}};
    for (auto i : merge(intervals)) cout << i; cout << endl;
    return 0;
}

int main()
{
    union_test();
}
