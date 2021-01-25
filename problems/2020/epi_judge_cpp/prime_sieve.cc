#include <vector>
#include <deque>
#include <iostream>

#include "test_framework/generic_test.h"
using std::vector;
using std::deque;
using std::cout;
using std::endl;

// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n)
{
  vector<int> primes;
  deque<bool> is_prime(n+1,true);
  is_prime[0] = is_prime[1] = false;
  for (int p = 2; p <= n; p++) {
    if (is_prime[p]) {
      primes.emplace_back(p);
      for (int i = p; i <= n; i += p) {
        is_prime[i] = false;
      }
    }
  }
  return primes;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
