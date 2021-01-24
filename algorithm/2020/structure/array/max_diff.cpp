#include <algorithm>
#include <vector>
#include <limits>
#include <iostream>

using namespace std;

double buy_n_sell_forward(vector<double> const & prices)
{
    double min_price = numeric_limits<double>::max(), max_profit = 0;
    for (auto price : prices) {
        double max_profit_sell_at_this_price = price - min_price;
        max_profit = max(max_profit, max_profit_sell_at_this_price);
        min_price = min(min_price, price);
    }
    return max_profit;
}

double buy_n_sell_backward(vector<double> const & prices)
{
    double max_price = numeric_limits<double>::min(), max_profit = 0;
    for (auto i = rbegin(prices); i != rend(prices); i++) {
        auto price = *i;
        double max_profit_buy_at_this_price = max_price - price;
        max_profit = max(max_profit, max_profit_buy_at_this_price);
        max_price = max(max_price, price);
    }
    return max_profit;
}

double buy_n_sell_twice(vector<double> const & prices)
{
    double min_price = numeric_limits<double>::max();
    double max_price = numeric_limits<double>::min();
    double max_profit = 0;
    vector<double> max_profit_sell_at_price(prices.size());
    for (int i = 0; i < prices.size(); i++) {
        min_price = min(min_price,prices[i]);
        double max_profit_sell_at_this_price = prices[i] - min_price;
        max_profit = max(max_profit, max_profit_sell_at_this_price);
        max_profit_sell_at_price[i] = max_profit_sell_at_this_price;
    }
    for (int i = (int)prices.size() - 1; i > 0; i--) {
        max_price = max(max_price, prices[i]);
        double max_profit_buy_at_this_price = max_price - prices[i];
        max_profit = max(max_profit, max_profit_buy_at_this_price + max_profit_sell_at_price[i-1]);
    }
    return max_profit;
}

int main()
{
    vector<double> prices = {310,315,275,295,260,270,290,230,255,250};
    cout << buy_n_sell_forward(prices) << endl;
    cout << buy_n_sell_backward(prices) << endl;

    prices = vector<double>{12,11,13,9,12,8,14,13,15};
    cout << buy_n_sell_forward(prices) << endl;
    cout << buy_n_sell_backward(prices) << endl;
    cout << buy_n_sell_twice(prices) << endl;
}

