#include <iostream>

long long gcd(long long a, long long b)
{
    if (b) return gcd(b,a%b);
    else return a;
}

int main()
{
    std::cout << gcd(6,9) << std::endl;
}

