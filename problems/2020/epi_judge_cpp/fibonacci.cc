#include "test_framework/generic_test.h"

#include <unordered_map>
using std::unordered_map;

auto fibonacci(int n) -> int
{
    int a = 0, b = 1;
    int f = n;
    for (int i = 2; i <= n; i++) {
        f = a + b; a = b; b = f;
    }
    return f;
}

int Fibonacci(int n)
{
  static unordered_map<int,int> m;
  if (n == 0 || n == 1) return n;
  else if (!m.count(n)) { m[n] = Fibonacci(n-1) + Fibonacci(n-2); }
  return m[n];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "fibonacci.cc", "fibonacci.tsv", &fibonacci,
                         DefaultComparator{}, param_names);
}
