#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    unsigned long long a = 0;
    long double b = 0;
    cin >> a >> b;
    cout << (unsigned long long)trunc(a*b) << endl;
}

