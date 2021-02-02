#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <random>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"

using std::abs;
using std::bind;
using std::default_random_engine;
using std::distance;
using std::generate_canonical;
using std::numeric_limits;
using std::random_device;
using std::unordered_map;
using std::vector;

int NonuniformRandomNumberGeneration(const vector<int>& values, const vector<double>& probabilities)
{
  vector<double> cumulative;
  partial_sum(cbegin(probabilities),cend(probabilities),back_inserter(cumulative));
  default_random_engine engine((random_device())());
  double canonical = generate_canonical<double,numeric_limits<double>::digits>(engine);
  int i = distance(cbegin(cumulative),upper_bound(cbegin(cumulative),cend(cumulative),canonical));
  return values[i];
}

bool NonuniformRandomNumberGenerationRunner(
    TimedExecutor& executor, const vector<int>& values,
    const vector<double>& probabilities) {
  constexpr int kN = 1000000;
  vector<int> results;

  executor.Run([&] {
    for (int i = 0; i < kN; ++i) {
      results.emplace_back(
          NonuniformRandomNumberGeneration(values, probabilities));
    }
  });

  unordered_map<int, int> counts;
  for (int result : results) {
    ++counts[result];
  }
  for (int i = 0; i < values.size(); ++i) {
    const int v = values[i];
    const double p = probabilities[i];
    if (kN * p < 50 || kN * (1.0 - p) < 50) {
      continue;
    }
    const double sigma = sqrt(kN * p * (1.0 - p));
    if (abs(counts[v] - (p * kN)) > 5 * sigma) {
      return false;
    }
  }
  return true;
}

void NonuniformRandomNumberGenerationWrapper(
    TimedExecutor& executor, const vector<int>& values,
    const vector<double>& probabilities) {
  RunFuncWithRetries(bind(NonuniformRandomNumberGenerationRunner,
                          std::ref(executor), std::cref(values),
                          std::cref(probabilities)));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "values", "probabilities"};
  return GenericTestMain(args, "nonuniform_random_number.cc",
                         "nonuniform_random_number.tsv",
                         &NonuniformRandomNumberGenerationWrapper,
                         DefaultComparator{}, param_names);
}
