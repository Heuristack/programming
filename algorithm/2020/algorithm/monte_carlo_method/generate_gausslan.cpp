#include <boost/histogram.hpp>
#include <boost/format.hpp>
#include <functional>
#include <algorithm>
#include <random>
#include <vector>
#include <sstream>
#include <iostream>

using namespace boost::histogram;
using namespace std;

template <typename device = random_device, typename engine = default_random_engine,
          typename distribution = normal_distribution<double>,
          typename result_type = typename distribution::result_type>
auto generate(result_type mean = 0, result_type stddev = 1) -> result_type
{
    static device dev;
    engine eng(dev());
    distribution dis(mean,stddev);
    return dis(eng);
}

int main()
{
    vector<double> values;
    for (int i = 0; i < 1000; i++) { values.push_back(generate(0.0,0.4)); }

    double sigma = 0;
    double mean = 0;
    for (double value : values) { sigma += value; }
    mean = sigma/values.size();
    cout << mean << endl;

    auto histogram = make_histogram(axis::regular<>(9, -1.0, 1.0, "x"));
    std::for_each(values.begin(), values.end(), std::ref(histogram));

    std::ostringstream os;
    for (auto && x : indexed(histogram, coverage::all)) {
        os << boost::format("bin %2i [%4.1f, %4.1f): %i\n")
        % x.index() % x.bin().lower() % x.bin().upper() % *x;
    }

    std::cout << os.str() << std::flush;
}

