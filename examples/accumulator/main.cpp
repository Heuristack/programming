#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

#include <iostream>

using namespace boost::accumulators;
using namespace std;

int main()
{
    accumulator_set<double, stats<tag::mean, tag::median, tag::moment<2>>> acc;
    acc(1.2); acc(2.3); acc(3.4); acc(4.5); acc(5.6);
    cout << "median = " << median(acc) << endl;
    cout << "moment = " << moment<2>(acc) << endl;
}

