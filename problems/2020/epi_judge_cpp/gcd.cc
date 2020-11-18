#include "test_framework/generic_test.h"

long long Gcd0(long long x, long long y)
{
  if (y) return Gcd0(y,x % y);
  else return x;
}

long long Gcd(long long x, long long y)
{
  while (y) {
    auto r = x % y;
    x = y;
    y = r;
  }
  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "gcd.cc", "gcd.tsv", &Gcd, DefaultComparator{},
                         param_names);
}
