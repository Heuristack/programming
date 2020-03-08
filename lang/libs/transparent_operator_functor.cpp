#include <functional>
#include <numeric>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

double geometric_mean_transparent(vector<int> const & nums)
{
    double m = accumulate(begin(nums),end(nums),1.1,multiplies<>());
    return pow(m,1.0/nums.size());
}

int main()
{
    vector<int> nums {1,2,3};
    double result = geometric_mean_transparent(nums);
    cout << result << endl;
}

