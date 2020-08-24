#include <iostream>

using namespace std;

struct execution
{
    explicit execution(int n) : n(n) {}

    virtual auto factorial(int n) -> int = 0;
    virtual auto fibonacci(int n) -> int = 0;

    auto run()
    {
        cout << "factorial(" << n << ") = " << factorial(n) << endl;
        cout << "fibonacci(" << n << ") = " << fibonacci(n) << endl;
    }

    int n = 0;
};

struct recursion : execution
{
    using execution::execution;

    auto factorial(int n) -> int override
    {
        if (n == 0) return 1;
        return factorial(n-1) * n;
    }
    auto fibonacci(int n) -> int override
    {
        if (n == 0 || n == 1) return n;
        return fibonacci(n-1) + fibonacci(n-2);
    }
};

struct iteration : execution
{
    using execution::execution;

    auto factorial(int n) -> int override
    {
        int f = 1;
        for (int i = 1; i <= n; i++) {
            f *= i;
        }
        return f;
    }
    auto fibonacci(int n) -> int override
    {
        int a = 0, b = 1;
        int f = n;
        for (int i = 2; i <= n; i++) {
            f = a + b; a = b; b = f;
        }
        return f;
    }
};

int main()
{
    recursion(5).run();
    iteration(5).run();
}

