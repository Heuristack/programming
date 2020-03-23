#include <iostream>
#include <vector>

using namespace std;

auto power(vector<int> s) -> vector<vector<int>>
{
    if (s.empty()) return {{}};
    auto p = power(vector<int> (next(begin(s)),end(s)));
    auto q = p;
    for (auto a : q) {
        a.push_back(*begin(s));
        p.push_back(a);
    }
    return p;
}

int main()
{
    for (auto const & s : power({1,2,3})) {
        cout << "{";
        for (auto const & e : s) cout << e;
        cout << "}";
    }
    cout << endl;
}

