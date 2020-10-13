#include <iostream>
#include <iomanip>
#include <optional>
#include <vector>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std;

#include "branch_n_bound.hpp"
#include "knapsack.hpp"
#include "knapsack.ipp"
#include "knapsack_bnb.hpp"
#include "knapsack_bnb.ipp"
#include "knapsack_powerset.ipp"

int main()
{
    initializer_list<item> items = {{40,40},{50,60},{30,10},{10,10},{10,3},{40,20},{30,60}};
    int maximum_allowable_weight = 100;
    node n(items,maximum_allowable_weight);
    cout << branch(n).sigma() << endl;
    cout << explore(n) << endl;
    cout << aggregate_subset(max_value_subset(vector_type<item>(items),maximum_allowable_weight)).value << endl;
}
// Kolesar, P.J., 1967. A branch and bound algorithm for the knapsack problem. Management science, 13(9), pp.723-735.

