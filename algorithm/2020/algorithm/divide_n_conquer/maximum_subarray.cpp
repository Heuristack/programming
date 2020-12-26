#include <algorithm>
#include <vector>
#include <limits>
#include <tuple>
#include <iostream>
#include <iterator>

using namespace std;

template <typename iterator>
auto maximum_subarray(iterator p, iterator m, iterator r)
{
    typename iterator::value_type lower_sum = 0;
    auto lower_max_sum = numeric_limits<typename iterator::value_type>::min();
    iterator lower = m;
    for (auto i = m; i > p; i--) {
        lower_sum += *prev(i);
        if (lower_sum > lower_max_sum) {
            lower_max_sum = lower_sum;
            lower = prev(i);
        }
    }
    typename iterator::value_type upper_sum = 0;
    auto upper_max_sum = numeric_limits<typename iterator::value_type>::min();
    iterator upper = m;
    for (auto i = m; i < r; i++) {
        upper_sum += *i;
        if (upper_sum > upper_max_sum) {
            upper_max_sum = upper_sum;
            upper = i;
        }
    }
    return make_tuple(lower, upper, lower_max_sum + upper_max_sum);
}

template <typename iterator>
auto maximum_subarray(iterator p, iterator r)
{
    auto d = distance(p,r);
    auto m = p + d/2;
    if (d == 1) return make_tuple(p,r,*m);
    auto [mlower,mupper,mmaxsum] = maximum_subarray(p,m,r);
    auto [llower,lupper,lmaxsum] = maximum_subarray(p,m);
    auto [rlower,rupper,rmaxsum] = maximum_subarray(m,r);
    if ((lmaxsum >= rmaxsum) && (lmaxsum >= mmaxsum)) return make_tuple(llower,lupper,lmaxsum);
    if ((rmaxsum >= lmaxsum) && (rmaxsum >= mmaxsum)) return make_tuple(rlower,rupper,rmaxsum);
    return make_tuple(mlower,mupper,mmaxsum);
}

// Introduction to algorithms.
// Cormen, T.H., Leiserson, C.E., Rivest, R.L. and Stein, C., 2009.
// MIT press. 4.1

auto maximum_subarray_kadane(vector<int> a) {
    int max_ending = 0;
    int max_slice = 0;
    for (auto const & e : a) {
//      cout << e << ":(" << max_ending << "," << max_slice << ")";
//      cout << "->";
        max_ending = max(0,max_ending+e);
        max_slice = max(max_slice, max_ending);
//      cout << "(" << max_ending << "," << max_slice << ")";
//      cout << endl;
    }
    return max_slice;
}

int maximum_subarray_dp(vector<int> a)
{
    int min_sum = 0, running_sum = 0, max_sum = 0;
    for (int i = 0; i < a.size(); i++) {
        running_sum += a[i];
        if (running_sum < min_sum) {
            min_sum = running_sum;
        }
        if (running_sum - min_sum > max_sum) {
            max_sum = running_sum - min_sum;
        }
    }
    return max_sum;
}

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

