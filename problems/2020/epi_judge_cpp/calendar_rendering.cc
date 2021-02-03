#include <algorithm>
#include <vector>

#include "test_framework/serialization_traits.h"
#include "test_framework/generic_test.h"

using std::vector;
using std::sort;
using std::max;

struct Event
{
  int start, finish;
};

struct EndPoint
{
  EndPoint(int t, bool s) : time(t), is_start(s) {}
  int time;
  bool is_start;
};

bool operator < (EndPoint const & a, EndPoint const & b)
{
  return (a.time != b.time) ? a.time < b.time : (a.is_start && !b.is_start);
}

int FindMaxSimultaneousEvents(vector<Event> const & A)
{
  if (A.empty()) return 0;
  vector<EndPoint> endpoints;
  for (auto const & e : A) {
    endpoints.emplace_back(e.start,true);
    endpoints.emplace_back(e.finish,false);
  }
  sort(begin(endpoints),end(endpoints));
  int num = 0, max_num = 0;
  for (auto const & e : endpoints) {
    if (e.is_start) num++;
    else num--;
    max_num = max(max_num,num);
  }
  return max_num;
}

namespace test_framework {
template <>
struct SerializationTrait<Event> : UserSerTrait<Event, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}

