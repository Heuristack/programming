long long gcd(long long a, long long b)
{
    if (b) return gcd(b,a%b);
    else return a;
}

