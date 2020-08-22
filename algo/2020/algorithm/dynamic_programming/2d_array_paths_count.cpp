#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

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

    auto compute_num_paths(state s) -> int
    {
        if (s.i == 0 && s.j == 0) {
            dp[s.i][s.j] = 1;
            return 1;
        }
        if (!dp[s.i][s.j]) {
            if (s.i == 0) { dp[s.i][s.j] = compute_num_paths(state(s.i,s.j-1)); return dp[s.i][s.j]; }
            if (s.j == 0) { dp[s.i][s.j] = compute_num_paths(state(s.i-1,s.j)); return dp[s.i][s.j]; }
            dp[s.i][s.j] = compute_num_paths(state(s.i,s.j-1)) + compute_num_paths(state(s.i-1,s.j));
        }
        return dp[s.i][s.j];
    }
    auto compute_num_paths() -> int { return compute_num_paths(state(m-1,n-1)); }

    vector<vector<int>> dp;
    int m = 0;
    int n = 0;
};

ostream & operator << (ostream & strm, space const & s)
{
    for (int i = 0; i < s.m; i++) {
    for (int j = 0; j < s.n; j++) {
        strm << setw(2) << setfill(' ') << s.dp[i][j];
    }   strm << endl;
    }
    return strm;
}

int main()
{
    space s(5,5);
    cout << s.compute_num_paths() << endl;
    cout << s;
}

