#include <iostream>
#include <vector>

using namespace std;

auto power(vector<int> s) -> vector<vector<int>>
{
    vector<vector<int>> p;
    for (auto const & e : s) {
        if (p.empty()) {
            p.push_back({});
            p.push_back({e});
        }
        else {
            auto q = p;
            for (auto r : q) {
                r.push_back(e);
                p.push_back(r);
            }
        }
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

