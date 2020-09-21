#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

auto permute(vector<int> s, int n) -> vector<vector<int>>
{
    static vector<vector<int>> permutations;
    static vector<int> path;

    if (!n) {
        permutations.push_back(path);
        return permutations;
    }

    for (auto i = begin(s); i != end(s); i++) {
        vector<int> c(begin(s),i);
        copy(next(i),end(s),back_inserter(c));
        path.push_back(*i);
        permute(c,n-1);
        path.pop_back();
    }

    return permutations;
}

int main()
{
    for (auto const & s : permute({1,2,3},2)) {
        for (auto const & e : s) cout << e;
        cout << endl;
    }
}

