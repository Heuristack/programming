#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

#include "constraint_satisfaction_problem.hpp"
#include "n-permutation_csp.hpp"
#include "n-permutation_csp.ipp"
#include "n-permutation.hpp"
#include "n-permutation.ipp"

template <typename type>
ostream & operator << (ostream & strm, vector<type> const v) {
    for (auto const & s : v) {
        for (auto const & e : s) strm << e;
        strm << " ";
    }
    return strm;
}

int main()
{
    cout << permutation({1,2,3,4,5},3).generate() << endl;
    cout << generate_permutation({1,2,3,4,5},3) << endl;
}

