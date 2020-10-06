#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>

using namespace std;

struct execution
{
    virtual auto generate_powerset(vector<int> s) -> vector<vector<int>> = 0;
    virtual auto run() -> void
    {
        for (auto const & s : generate_powerset({1,2,3})) {
            cout << "{";
            for (auto const & e : s) cout << e;
            cout << "}";
        }
        cout << endl;
    }
};

struct recursion : execution
{
    using execution::execution;
    auto generate_powerset(vector<int> s) -> vector<vector<int>> override;
    auto run() -> void override { cout << "recursion: "; return execution::run(); }
};

struct iteration : execution
{
    using execution::execution;
    auto generate_powerset(vector<int> s) -> vector<vector<int>> override;
    auto run() -> void override { cout << "execution: "; return execution::run(); }
};

struct optimized : execution
{
    using execution::execution;
    auto generate_powerset(vector<int> s) -> vector<vector<int>> override;
    auto run() -> void override { cout << "optimized: "; return execution::run(); }
};

#include "generate_powerset.ipp"

int main()
{
    recursion().run();
    iteration().run();
    optimized().run();
}

