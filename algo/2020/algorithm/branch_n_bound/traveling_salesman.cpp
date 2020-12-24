#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <set>
#include <limits>
#include <utility>
#include <tuple>
#include <algorithm>

using namespace std;

#include "traveling_salesman.hpp"
#include "traveling_salesman_bnb.ipp"
namespace csp {
#include "traveling_salesman_csp.ipp"
}

int main()
{
    // branch-bound
    auto e = explore(node(cm));
    show(e);
    show_path(e.path);
    cout << endl;

    // brute-force
    auto const & min_cost_path = csp::explore(csp::node({1},{2,3,4,5,6}));
    csp::show(min_cost_path);
    cout << " = ";
    cout << csp::cost(min_cost_path,cm) << endl;

}

