#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::numeric_limits;
using std::max;
using std::min;

double BuyAndSellStockOnce(const vector<double>& prices)
{
  double min_price = numeric_limits<double>::max();
  double max_p = 0;
  for (auto price : prices) {
    double max_0 = price - min_price;
    max_p = max(max_p,max_0);
    min_price = min(min_price,price);
  }
  return max_p;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}

