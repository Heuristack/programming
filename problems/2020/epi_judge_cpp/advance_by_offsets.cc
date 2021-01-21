#include <vector>
#include <cmath>
#include <iostream>

#include "test_framework/generic_test.h"
using std::vector;
using std::max;

bool CanReachEnd(const vector<int> & max_advance_steps)
{
  int p = 0, q = max_advance_steps.size() - 1;
  for (int i = 0; i <= p && p < q; i++) {
    p = max(p,max_advance_steps[i] + i);
//  std::cout << "[" << i << "] = " << p << std::endl;
  }
  return p >= q;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}

