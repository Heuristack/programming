long long gcd_recursive(long long a, long long b)
{
    if (b) return gcd_recursive(b,a%b);
    else return a;
}

long long gcd_iterative(long long a, long long b)
{
    while (b) {
        auto r = a % b;
        a = b; b = r;
    }
    return a;
}

