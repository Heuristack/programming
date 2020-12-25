#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

#include <iostream>

using namespace boost::accumulators;
using namespace std;

int main()
{
    accumulator_set<double, stats<tag::min, tag::max, tag::variance>> acc;
    acc(3.1); acc(3.0); acc(3.2); acc(3.4); acc(3.3);
    cout << "avg = " << mean(acc) << endl;
    cout << "var = " << variance(acc) << endl;
    cout << "min = " << extract::min(acc) << endl;
    cout << "max = " << extract::max(acc) << endl;
}

