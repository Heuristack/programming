#include <iostream>
#include <iomanip>

using namespace std;

struct Execution
{
    Execution(unsigned int N): number(N) {}

    virtual unsigned int Factorial(unsigned int) = 0;
    virtual unsigned int Fibonacci(unsigned int) = 0;

    void Run()
    {
        cout << "Factorial(" << number << ") = " << Factorial(number) << "\n";
        cout << "Fibonacci(" << number << ") = " << Fibonacci(number) << "\n";
    }

    unsigned int number = 0;
};

struct Iteration : Execution
{
    Iteration(unsigned int N): Execution(N) {};

    auto Factorial(unsigned int N) -> unsigned int override
    {
        auto F = 1;
        for (auto I = 1; I <= N; I++) {
            F *= I;
        }
        return F;
    }

    auto Fibonacci(unsigned int N) -> unsigned int override
    {
        auto D = 0, E = 1;
        auto F = N;
        for (auto I = 2; I <= N; I++) {
            F = E + D; D = E; E = F;
        }
        return F;
    }
};

struct Recursion : Execution
{
    Recursion(unsigned int N): Execution(N) {}

    auto Factorial(unsigned int N) -> unsigned int override
    {
        if (N == 0) return 1;
        else return Factorial(N - 1) * N;
    }

    auto Fibonacci(unsigned int N) -> unsigned int override
    {
        if (N <= 1) return N;
        else return Fibonacci(N - 2) + Fibonacci(N - 1);
    }

};

int main()
{
    Recursion(5).Run();
    Iteration(5).Run();
}

