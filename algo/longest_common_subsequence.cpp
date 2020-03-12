#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

string longest_common_subsequence(string const & a, string const & b)
{
    vector<vector<int>> dp(a.size()+1);
    for (auto & row : dp) { row.resize(b.size()+1); }

    for (int i = 0; i <= a.size(); i++) dp[i][0] = 0;
    for (int j = 0; j <= b.size(); j++) dp[0][j] = 0;

    enum class UpdateDirection { L = -1, U = 1, D = 0 };
    vector<vector<UpdateDirection>> dt(a.size()+1);
    for (auto & row : dt) { row.resize(b.size()+1); }

    for (int i = 1; i <= a.size(); i++) {
    for (int j = 1; j <= b.size(); j++) {
        if (a[i-1] == b[j-1]) {
            dp[i][j] = dp[i-1][j-1] + 1;
            dt[i][j] = UpdateDirection::D;
        }
        else {
            if (dp[i-1][j] >= dp[i][j-1]) {
                dp[i][j] = dp[i-1][j];
                dt[i][j] = UpdateDirection::U;
            }
            else {
                dp[i][j] = dp[i][j-1];
                dt[i][j] = UpdateDirection::L;
            }
        }
    }
    }

    string lcs;
    int i = a.size();
    int j = b.size();
    while (i != 0 && j != 0) {
        switch(dt[i][j]) {
            case UpdateDirection::D:
                i--; j--;
                assert(a[i] == b[j]);
                lcs += a[i];
                break;
            case UpdateDirection::U: i--; break;
            case UpdateDirection::L: j--; break;
            default: break;
        }
    }

    return lcs;
}

int main()
{
    string const X = "ABCBDAB";
    string const Y = "BDCABA";
    auto lcs = longest_common_subsequence(X,Y);
    cout << "LongCommonSequence(" << quoted(X) << "," << quoted(Y) << ") = " << lcs << "(" << lcs.size() << ")" << endl;
}


