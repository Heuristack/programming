#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

vector<long> generate_p(long n)
{
    vector<long> s(n+1,1);
    s[0] = s[1] = 0;
    for (long i = 2; i * i <= n; i++) {
        if (s[i] == 1) {
            for (long k = i * i; k <= n; k += i) {
                s[k] = 0;
            }
        }
    }
    vector<long> v;
    for (auto i = 2u; i < s.size(); i++) {
        if (s[i] != 0) {
            v.push_back(i);
        }
    }
    return v;
}

vector<long> generate_z(long n)
{
    vector<long> v;
    long z = 0;
    for (long p : generate_p(n)) {
        for (long e = 1; (z = pow(p,e)) < n; e++) {
            v.push_back(z);
        }
    }
    return v;
}

int main()
{
    long n = 0;
    cin >> n;
    vector<long> z = generate_z(n);
    if (z.empty()) {
        cout << 0 << endl;
        return 0;
    }
    long i = 0;
    while (n/z[i] > 0 && n%z[i] == 0) {
        n = n/z[i];
        i++;
    }
    cout << i << endl;
    return 0;
}

