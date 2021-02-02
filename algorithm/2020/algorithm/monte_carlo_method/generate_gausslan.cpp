#include <iostream>
#include <random>
#include <vector>

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
    double sigma = 0;
    double mean = 0;
    for (int i = 0; i < 1000; i++) { values.push_back(generate(5.0,4.0)); }
    for (double value : values) { sigma += value; }
    mean = sigma/values.size();
    cout << mean << endl;
}

