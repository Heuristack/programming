#include "test_framework/generic_test.h"

long long gcd(long long a, long long b)
{
  if (b) return gcd(b,a%b);
  else return a;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "euclidean_gcd.cc", "gcd.tsv", &gcd,
                         DefaultComparator{}, param_names);
}
