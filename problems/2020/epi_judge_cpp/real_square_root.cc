#include "test_framework/generic_test.h"
#include <limits>

using std::numeric_limits;

int compare(double a, double b)
{
  double d = (a - b)/b;
  if (d < -numeric_limits<double>::epsilon()) return -1;
  if (d > +numeric_limits<double>::epsilon()) return +1;
  return 0;
}

double SquareRoot(double x)
{
  double p,q;
  if (x < 1.0/*compare(x,1.0) < 0*/) { p = x; q = 1.0; }
  else { p = 1.0; q = x; }

  while (compare(p,q) < 0) {
    double m = p + (q - p)*0.5;
    double s = m * m;
    if (compare(s,x) == 0) return m;
    if (compare(s,x) < 0) p = m;
    else /*if (compare(s,x) > 0)*/ q = m;
  }
  return p;
}

int main(int argc, char* argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}

