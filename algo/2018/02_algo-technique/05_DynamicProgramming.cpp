#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

int dynamic_coin_changing(vector<int> coins, int a)
{
    vector<vector<int>> dp(coins.size() + 1);
    for (auto & v : dp) v.resize(a + 1, 0);
    for (auto i = 1u; i < a + 1; i++) {
        dp[0][i] = numeric_limits<int>::max();
    }

    for (auto i = 1u; i < dp.size(); i++) {
        for (auto j = 1u; j < coins[i-1]; j++) {
            dp[i][j] = dp[i-1][j];
        }
        for (auto j = coins[i-1]; j < a + 1; j++) {
            dp[i][j] = min(dp[i][j-coins[i-1]] + 1, dp[i-1][j]);
        }
    }
    return dp[coins.size()][a];
}

int main()
{
    vector<int> coins1 = {1,2,5};
    vector<int> coins2 = {1,3,4};
    auto amount = 6;
    cout << dynamic_coin_changing(coins1,amount) << endl;
    cout << dynamic_coin_changing(coins2,amount) << endl;
}

