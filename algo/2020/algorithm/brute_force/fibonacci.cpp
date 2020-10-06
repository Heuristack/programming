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

#include "fibonacci.ipp"

int main()
{
    recursion().run();
    iteration().run();
}

