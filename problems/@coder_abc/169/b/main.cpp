#include <algorithm>
#include <vector>
#include <limits>
#include <cmath>
#include <iostream>

using namespace std;

long long maxvalue = 0;
long long solution(vector<long long> v)
{
    long long product = 1;
    for (int i = 0; i < v.size(); i++) {
        product *= v[i];
    }
    if (product > maxvalue) {
        return -1;
    }
    return product;
}

int main()
{
    maxvalue = pow(10,18);
    long long n;
    cin >> n;
    vector<long long> v(n);
    long long r = -1;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        if (v[i] == 0) {
            r = 0;
        }
    }
    if (r != 0) {
        cout << solution(v) << endl;
    }
    else {
        cout << r << endl;
    }
}

