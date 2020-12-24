#include <iostream>

using namespace std;

struct execution
{
    explicit execution(int n = 5) : n(n) {}
    virtual auto run() -> void { cout << "factorial(" << n << ") = " << factorial(n) << endl; }
    virtual auto factorial(int n) -> int = 0;
    int n = 0;
};

struct recursion : execution
{
    using execution::execution;
    auto run() -> void override { cout << "recursion::"; return execution::run(); }
    auto factorial(int n) -> int override;
};

struct iteration : execution
{
    using execution::execution;
    auto run() -> void override { cout << "iteration::"; return execution::run(); }
    auto factorial(int n) -> int override;
};

#include "factorial.ipp"

int main()
{
    recursion().run();
    iteration().run();
}

