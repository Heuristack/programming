#include "test_framework/generic_test.h"

#include <array>
using std::array;

int ChangeMaking(int cents)
{
  array<int,6> const coins{100,50,25,10,5,1};
  int num_coins = 0;
  for (auto coin : coins) {
     num_coins += cents / coin;
     cents = cents % coin;
  }
  return num_coins;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"cents"};
  return GenericTestMain(args, "making_change.cc", "making_change.tsv",
                         &ChangeMaking, DefaultComparator{}, param_names);
}
