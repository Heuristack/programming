auto recursion::fibonacci(int n) -> int
{
    if (n == 0 || n == 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

auto iteration::fibonacci(int n) -> int
{
    int a = 0, b = 1;
    int f = n;
    for (int i = 2; i <= n; i++) {
        f = a + b; a = b; b = f;
    }
    return f;
}

