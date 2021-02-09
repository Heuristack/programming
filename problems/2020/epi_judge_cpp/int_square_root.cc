#include "test_framework/generic_test.h"

int SquareRoot(int k)
{
  int p = 0,q = k;
  while (p <= q) {
    if (long m = p + (q-p)/2; m*m > k) q = m - 1; // note : use long to avoid overflow
    else p = m + 1;
  }
  return p - 1;
}

int main(int argc, char* argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}

