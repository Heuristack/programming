#include "test_framework/generic_test.h"

#include <vector>

using std::vector;

struct state
{
    state(int i, int j) : i(i), j(j) {}
    state() : state(0,0) {}
    int i = 0;
    int j = 0;
};

struct space
{
    space(int m, int n): m(m), n(n)
    {
        for (int i = 0; i < m; i++) dp.push_back(vector<int> (n,0));
    }

    auto count_paths(state s) -> int
    {
        if (s.i == 0 && s.j == 0) {
            dp[s.i][s.j] = 1;
            return 1;
        }
        if (!dp[s.i][s.j]) {
            if (s.i == 0) { dp[s.i][s.j] = count_paths(state(s.i,s.j-1)); return dp[s.i][s.j]; }
            if (s.j == 0) { dp[s.i][s.j] = count_paths(state(s.i-1,s.j)); return dp[s.i][s.j]; }
            dp[s.i][s.j] = count_paths(state(s.i,s.j-1)) + count_paths(state(s.i-1,s.j));
        }
        return dp[s.i][s.j];
    }
    auto count_paths() -> int { return count_paths(state(m-1,n-1)); }

    vector<vector<int>> dp;
    int m = 0;
    int n = 0;
};

int NumberOfWays(int n, int m)
{
  return space(n,m).count_paths();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
