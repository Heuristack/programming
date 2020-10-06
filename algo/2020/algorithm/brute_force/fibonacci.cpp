#include <iostream>

using namespace std;

struct execution
{
    explicit execution(int n = 5) : n(n) {}
    virtual auto run() -> void { cout << "fibonacci(" << n << ") = " << fibonacci(n) << endl; }
    virtual auto fibonacci(int n) -> int = 0;
    int n = 0;
};

struct recursion : execution
{
    using execution::execution;
    auto run() -> void override { cout << "recursion::"; return execution::run(); }
    auto fibonacci(int n) -> int override;
};

struct iteration : execution
{
    using execution::execution;
    auto run() -> void override { cout << "iteration::"; return execution::run(); }
    auto fibonacci(int n) -> int override;
};

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

int main()
{
    recursion().run();
    iteration().run();
}

