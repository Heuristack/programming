#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int greedy_coin_changing(vector<int> coins, int a)
{
    vector<pair<int,int>> changes;
    for (auto i = rbegin(coins); i != rend(coins); i++) {
        changes.push_back({*i,a/(*i)});
        a = a % (*i);
    }
//  for (auto [c,n] : changes) { cout << c << ":" << n << endl; }
    return accumulate(begin(changes),end(changes),0,[](auto a, auto i){
        auto [_,n] = i; return a + n;
    });
}

int main()
{
    vector<int> coins1 = {1,2,5};
    vector<int> coins2 = {1,3,4};
    auto amount = 6;
    cout << greedy_coin_changing(coins1,amount) << endl;
    cout << greedy_coin_changing(coins2,amount) << endl;
}

