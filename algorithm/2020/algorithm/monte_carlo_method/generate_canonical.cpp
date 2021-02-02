#include <iostream>
#include <random>
#include <vector>

using namespace std;

template <typename device = random_device, typename engine = default_random_engine>
auto generate() -> double
{
    static device dev;
    engine eng(dev());
    return generate_canonical<double,10>(eng);
}

int main()
{
    vector<double> values;
    double sigma = 0;
    double mean = 0;
    for (int i = 0; i < 1000; i++) { values.push_back(generate()); }
    for (double value : values) { sigma += value; }
    mean = sigma/values.size();
    cout << mean << endl;
}

