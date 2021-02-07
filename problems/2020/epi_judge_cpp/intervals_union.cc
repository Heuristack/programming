#include <algorithm>
#include <vector>
#include <map>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"

using std::vector;
using std::map;
using std::sort;
using std::any_of;

struct Interval {
  struct Endpoint {
    bool is_closed;
    int val;
  };

  Endpoint left, right;
};

struct interval
{
    interval(int p, int q, int op, int oq): p(p),q(q),op(op),oq(oq) {}
    interval(int p, int q): interval(p,q,0,0) {}
    int p,q,op,oq;
};

struct endpoint
{
    endpoint(int e, int i, int m, int o): e(e),i(i),m(m),o(o) {}
    endpoint(int e, int i, int m): endpoint(e,i,m,0) {}
    int e,i,m,o; // m - begin(0),end(1); o - open(1),close(0);
};

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

vector<Interval> UnionOfIntervals(vector<Interval> Intervals)
{
  vector<interval> intervals;
  for (auto const & I : Intervals) {
    interval i(I.left.val,I.right.val);
    if (I.left.is_closed) i.op = 0; else i.op = 1;
    if (I.right.is_closed) i.oq = 0; else i.oq = 1;
    intervals.push_back(i);
  }
  vector<Interval> results;
  for (auto const & i : merge(intervals)) {
    Interval I;
    I.left.val = i.p; I.right.val = i.q;
    I.left.is_closed = (i.op != 1); I.right.is_closed = (i.oq != 1);
    results.push_back(I);
  }
  return results;
}

struct FlatInterval {
  int left_val;
  bool left_is_closed;
  int right_val;
  bool right_is_closed;

  FlatInterval(int left_val, bool left_is_closed, int right_val,
               bool right_is_closed)
      : left_val(left_val),
        left_is_closed(left_is_closed),
        right_val(right_val),
        right_is_closed(right_is_closed) {}

  explicit FlatInterval(Interval in)
      : left_val(in.left.val),
        left_is_closed(in.left.is_closed),
        right_val(in.right.val),
        right_is_closed(in.right.is_closed) {}

  operator Interval() const {
    return {{left_is_closed, left_val}, {right_is_closed, right_val}};
  }

  bool operator==(const FlatInterval& rhs) const {
    return std::tie(left_val, left_is_closed, right_val, right_is_closed) ==
           std::tie(rhs.left_val, rhs.left_is_closed, rhs.right_val,
                    rhs.right_is_closed);
  }
};

namespace test_framework {
template <>
struct SerializationTrait<FlatInterval>
    : UserSerTrait<FlatInterval, int, bool, int, bool> {};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const FlatInterval& i) {
  return out << (i.left_is_closed ? '<' : '(') << i.left_val << ", "
             << i.right_val << (i.right_is_closed ? '>' : ')');
}

std::vector<FlatInterval> UnionOfIntervalsWrapper(
    TimedExecutor& executor, const std::vector<FlatInterval>& intervals) {
  std::vector<Interval> casted;
  for (const FlatInterval& i : intervals) {
    casted.push_back(static_cast<Interval>(i));
  }

  std::vector<Interval> result =
      executor.Run([&] { return UnionOfIntervals(casted); });

  return {begin(result), end(result)};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "intervals"};
  return GenericTestMain(args, "intervals_union.cc", "intervals_union.tsv",
                         &UnionOfIntervalsWrapper, DefaultComparator{},
                         param_names);
}
