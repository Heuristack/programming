#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> PlusOne(vector<int> A)
{
  A.back()++;
  int b = 10;
  int q = 0, r = 0;
  for (auto i = rbegin(A); i != rend(A); i++) {
    q = (*i)/b;
    r = (*i)%b;
    if (i != rend(A) && q > 0) { (*next(i)) += q; (*i) = r; }
  }
  if (q > 0) A.insert(A.begin(),q);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}

