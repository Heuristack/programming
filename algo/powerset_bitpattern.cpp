#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>

using namespace std;

auto power(vector<int> s) -> vector<vector<int>>
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
    for (auto const & s : power({1,2,3})) {
        cout << "{";
        for (auto const & e : s) cout << e;
        cout << "}";
    }
    cout << endl;
}

