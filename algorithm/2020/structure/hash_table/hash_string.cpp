#include <iostream>
#include <string>

using namespace std;

auto hash_string(string const & s, long modulus) -> long
{
    long constexpr multiplier = 997;
    long value = 0;
    for (auto c : s) {
        value = (value * multiplier + c) % modulus;
    }
    return value;
}

int main()
{
    cout << hash_string("hash string",200) << endl;
}

