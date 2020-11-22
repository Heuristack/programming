#include <vector>
#include <bitset>

#include "test_framework/generic_test.h"
using std::vector;
using std::bitset;

inline auto generate_powerset_0(vector<int> s) -> vector<vector<int>>
{
  vector<vector<int>> p = {{}};
  for (auto e : s) {
    for (auto b : decltype(p)(p)) {
      b.push_back(e);
      p.push_back(b);
    }
  }
  return p;
}

inline auto generate_powerset_1(vector<int> s) -> vector<vector<int>>
{
  vector<vector<int>> p;
  auto const n = 1 << s.size();
  for (auto i = 0; i < n; i++) {
    auto b = bitset<sizeof(decltype(i))>(i);
    vector<int> q;
    for (auto k = 0; k < b.size(); k++) {
      if (b[k]) q.push_back(s[k]);
    }
    p.push_back(q);
  }
  return p;
}

vector<vector<int>> GeneratePowerSet(const vector<int>& s)
{
  return generate_powerset_0(s);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input_set"};
  return GenericTestMain(args, "power_set.cc", "power_set.tsv",
                         &GeneratePowerSet, UnorderedComparator{}, param_names);
}
