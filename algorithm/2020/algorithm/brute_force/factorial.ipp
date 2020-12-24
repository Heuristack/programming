auto recursion::factorial(int n) -> int
{
    if (n == 0) return 1;
    return factorial(n-1) * n;
}

auto iteration::factorial(int n) -> int
{
    int f = 1;
    for (int i = 1; i <= n; i++) {
        f *= i;
    }
    return f;
}

