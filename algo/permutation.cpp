#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

auto permutation(vector<int> s, int n) -> vector<vector<int>>
{
    static vector<vector<int>> perms;
    static vector<int> path;

    if (!n) {
        perms.push_back(path);
        return perms;
    }

    for (auto i = begin(s); i != end(s); i++) {
        vector<int> c(begin(s),i);
        copy(next(i),end(s),back_inserter(c));
        path.push_back(*i);
        permutation(c,n-1);
        path.pop_back();
    }

    return perms;
}

int main()
{
    for (auto const & s : permutation({1,2,3},2)) {
        for (auto const & e : s) cout << e;
        cout << endl;
    }
}

