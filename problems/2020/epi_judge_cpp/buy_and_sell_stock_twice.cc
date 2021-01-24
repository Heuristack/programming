#include <algorithm>
#include <vector>
#include <limits>
#include <iostream>

#include "test_framework/generic_test.h"
using std::vector;
using std::max;
using std::min;
using std::numeric_limits;
using std::cout;
using std::endl;

double BuyAndSellStockTwice(const vector<double>& prices)
{
  int n = prices.size();

  double min_price = numeric_limits<double>::max();
  double max_price = numeric_limits<double>::min();
  double max_0 = 0;
  double max_1 = 0;
  vector<double> max_v0(n);
  vector<double> max_v1(n);

  for (int i = 0; i <= n-1; i++) {
    double price = prices[i];
    min_price = min(min_price,price);
    double max_s = price - min_price;
    max_0 = max(max_0,max_s);
    max_v0[i] = max_0;
  }

  for (int i = n-1; i >= 0; i--) {
    double price = prices[i];
    max_price = max(max_price,price);
    double max_b = max_price - price;
    max_1 = max(max_1,max_b);
    max_v1[i] = max_1;
  }

  double max_p = 0;
  for (int i = 1; i < n; i++) {
    max_p = max(max_p, max_v0[i-1]+max_v1[i]);
  }
  max_p = max(max_p,max_0);
  max_p = max(max_p,max_1);

  return max_p;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}

