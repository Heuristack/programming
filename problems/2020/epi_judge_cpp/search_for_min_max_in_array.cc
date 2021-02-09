#include <algorithm>
#include <vector>
#include <limits>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"

using std::vector;
using std::min;
using std::max;
using std::minmax;
using std::numeric_limits;

struct MinMax { int smallest, largest; };

MinMax FindMinMax0(vector<int> const & a)
{
  int min_num = numeric_limits<int>::max();
  int max_num = numeric_limits<int>::min();
  for (auto num : a) {
    min_num = min(min_num,num);
    max_num = max(max_num,num);
  }
  return {min_num,max_num};
}

MinMax FindMinMax(vector<int> const & a)
{
  auto n = a.size();
  if (n == 1) return {a[0],a[0]};
  int min_num = numeric_limits<int>::max();
  int max_num = numeric_limits<int>::min();
  for (int i = 0; i + 1 < n; i += 2) {
    auto [p,q] = minmax(a[i],a[i+1]);
    min_num = min(min_num,p);
    max_num = max(max_num,q);
  }
  if (n % 2) {
    min_num = min(min_num,a[n-1]);
    max_num = max(max_num,a[n-1]);
  }
  return {min_num,max_num};
}

namespace test_framework {
template <>
struct SerializationTrait<MinMax> : UserSerTrait<MinMax, int, int> {};
}  // namespace test_framework

bool operator==(const MinMax& lhs, const MinMax& rhs) {
  return std::tie(lhs.smallest, lhs.largest) ==
         std::tie(rhs.smallest, rhs.largest);
}

std::ostream& operator<<(std::ostream& out, const MinMax& x) {
  return out << "min: " << x.smallest << ", max: " << x.largest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_for_min_max_in_array.cc",
                         "search_for_min_max_in_array.tsv", &FindMinMax,
                         DefaultComparator{}, param_names);
}

