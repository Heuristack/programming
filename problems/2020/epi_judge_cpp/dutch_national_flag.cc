#include <algorithm>
#include <vector>
#include <array>
#include <utility>
#include <iostream>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::vector;
using std::swap;

enum class Color { kRed, kWhite, kBlue };

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr)
{
  if (!A_ptr || A_ptr->empty()) return;
  auto & A = (*A_ptr);
  auto m = A[pivot_index];
  int p = 0, i = 0, r = size(A);
  while (i < r) {
    if (A[i] == m) { i++; }
    else if (A[i] < m) { swap(A[p++],A[i++]); }
    else { swap(A[--r],A[i]); }
  }
  return;
}

void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
