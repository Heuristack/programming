#include <algorithm>
#include <vector>
#include <map>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"

using std::vector;
using std::map;

struct Interval { int left, right; };
struct interval { interval(int p, int q): p(p),q(q){} int p,q; };
struct endpoint { endpoint(int e, int i, int m): e(e),i(i),m(m) {} int e,i,m; };

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
            auto i = merge(stack);
            if (i.p != i.q) {
                results.push_back(i);
            }
        }
    }

    return results;
}

vector<Interval> AddInterval(const vector<Interval>& disjoint_intervals, Interval new_interval)
{
  vector<interval> intervals;
  for (auto const & i : disjoint_intervals) { intervals.emplace_back(i.left,i.right); }
  intervals.emplace_back(new_interval.left, new_interval.right);
  vector<Interval> results;
  for (auto const & i : merge(intervals)) { Interval I; I.left = i.p; I.right = i.q; results.push_back(I); }
  return results;
}

namespace test_framework {
template <>
struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("length({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Interval& x) {
    return {x.right - x.left};
  }
};

}  // namespace test_framework

bool operator==(const Interval& a, const Interval& b) {
  return a.left == b.left && a.right == b.right;
}

std::ostream& operator<<(std::ostream& out, const Interval& i) {
  return PrintTo(out, std::make_tuple(i.left, i.right));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"disjoint_intervals", "new_interval"};
  return GenericTestMain(args, "interval_add.cc", "interval_add.tsv",
                         &AddInterval, DefaultComparator{}, param_names);
}

