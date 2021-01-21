#include <vector>

#include "test_framework/timed_executor.h"
#include "test_framework/generic_test.h"

using std::vector;
// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr)
{
  if (!A_ptr || A_ptr->empty()) return 0;
  auto & A = *A_ptr;
  int w = 1;
  for (int i = 1; i < A.size(); i++) {
    if (A[w-1] != A[i]) {
      A[w++] = A[i];
    }
  }
  return w;
}

vector<int> DeleteDuplicatesWrapper(TimedExecutor& executor, vector<int> A) {
  int end = executor.Run([&] { return DeleteDuplicates(&A); });
  A.resize(end);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(
      args, "sorted_array_remove_dups.cc", "sorted_array_remove_dups.tsv",
      &DeleteDuplicatesWrapper, DefaultComparator{}, param_names);
}

