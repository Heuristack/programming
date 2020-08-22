#include <algorithm>
#include <numeric>
#include <vector>
#include <tuple>
#include <utility>
#include <iostream>

using namespace std;

auto greedy_coin_changing(vector<int> s, int a) -> vector<pair<int,int>>
{
    vector<pair<int,int>> changes;
    sort(rbegin(s),rend(s));
    for (auto const & e : s) {
        changes.emplace_back(e,a/e);
        a %= e;
    }
    return changes;
}

int main()
{
    vector<int> coins{1,3,4};
    auto changes = greedy_coin_changing(coins,6);
    cout << accumulate(begin(changes),end(changes),0,[](auto const & a, auto const & i) {
        return a + get<1>(i);
    }) << endl;
    for (auto const & [c,n] : changes) {
        cout << c << ":" << n << endl;
    }
}

