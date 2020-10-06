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


auto recursion::generate_powerset(vector<int> s) -> vector<vector<int>>
{
    if (s.empty()) return {{}};
    auto p = recursion::generate_powerset(vector<int>(next(begin(s)),end(s)));
    for (auto a : decltype(p)(p)) {
        a.push_back(*begin(s));
        p.push_back(a);
    }
    return p;
}

auto iteration::generate_powerset(vector<int> s) -> vector<vector<int>>
{
    vector<vector<int>> p;
    for (auto e : s) {
        if (!p.empty()) {
            for (auto q : decltype(p)(p)) {
                q.push_back(e);
                p.push_back(q);
            }
        }
        else {
            p.push_back({});
            p.push_back({e});
        }
    }
    return p;
}

auto optimized::generate_powerset(vector<int> s) -> vector<vector<int>>
{
    vector<vector<int>> p;
    auto const n = 1 << s.size();
    for (auto i = 0; i < n; i++) {
        auto b = bitset<sizeof(decltype(i))>(i);
        vector<int> q;
        for (auto k = 0; k < b.size(); k++) {
            if (b[k]) q.push_back(s[k]);
        }
        p.push_back(q);
    }
    return p;
}

int main()
{
    recursion().run();
    iteration().run();
    optimized().run();
}

