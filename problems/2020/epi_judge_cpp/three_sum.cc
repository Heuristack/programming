#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

#include "test_framework/generic_test.h"

using std::vector;
using std::begin;
using std::endl;
using std::next;
using std::prev;

bool HasTwoSum(vector<int> v, int k)
{
    assert(std::is_sorted(begin(v),end(v)));
    auto p = begin(v);
    auto q = prev(end(v));
    while (p != next(q)) {
        auto s = *p + *q;
        if (s == k) { return true; }
        else if (s < k) { p = next(p); }
        else if (s > k) { q = prev(q); }
    }
    return false;
}

bool HasThreeSum(vector<int> A, int t)
{
  std::sort(begin(A),end(A));
  return std::any_of(begin(A),end(A),[A,t](auto k){ return HasTwoSum(A,t-k); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}
