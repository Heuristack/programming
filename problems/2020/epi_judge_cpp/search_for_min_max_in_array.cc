#include <algorithm>
#include <vector>
#include <limits>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"

using std::vector;
using std::min;
using std::max;
using std::numeric_limits;

struct MinMax { int smallest, largest; };

MinMax FindMinMax(vector<int> const & a)
{
  int min_num = numeric_limits<int>::max();
  int max_num = numeric_limits<int>::min();
  for (auto num : a) {
    min_num = min(min_num,num);
    max_num = max(max_num,num);
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

