#include <algorithm>
#include <vector>
#include <limits>
#include <tuple>
#include <iostream>
#include <iterator>

using namespace std;

#include "maximum_subarray_kadane.ipp"
#include "maximum_subarray_dnc.ipp"
#include "maximum_subarray_dp.ipp"

int main()
{
    vector<vector<int>> vv = {
        {904,40,523,12,-335,-385,-124,481,-31},
        {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7},
        {5,-7,3,5,-2,4,-1},
        {-2,1,2},
        {-2}
    };
    for (auto const & v : vv) {
        cout << get<2>(maximum_subarray(begin(v),end(v)));
        cout << "=";
        cout << maximum_subarray_kadane(v);
        cout << "=";
        cout << maximum_subarray_dp(v);
        cout << endl;
    }
}

