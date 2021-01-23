#include <algorithm>
#include <vector>
#include <limits>
#include <iostream>

using namespace std;

double buy_n_sell(vector<double> const & prices)
{
    double min_price = numeric_limits<double>::max(), max_profit = 0;
    for (auto price : prices) {
        double max_profit_sell_at_this_price = price - min_price;
        max_profit = max(max_profit, max_profit_sell_at_this_price);
        min_price = min(min_price, price);
    }
    return max_profit;
}

int main()
{
    vector<double> prices = {310,315,275,295,260,270,290,230,255,250};
    cout << buy_n_sell(prices) << endl;
}

