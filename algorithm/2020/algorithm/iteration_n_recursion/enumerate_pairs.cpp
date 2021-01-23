#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>

using namespace std;

auto enumerate_tuple(int a, int b)
{
    vector<tuple<int,int,int,int>> tuples;
    for (int p = a; p <= b; p++) {
    for (int i = a; i <= b; i++) {
    for (int j = a; j <= b; j++) {
    for (int q = a; q <= b; q++) {
        if (i <= j && j <= p && p <= q) {
            tuples.push_back(make_tuple(p,i,j,q));
        }
    }
    }
    }
    }
    return tuples;
}

int main()
{
    auto pairs = enumerate_tuple(0,3);
    for (auto [p,i,j,q] : pairs) {
        cout << "(" << p << "," << i << "," << j << "," << q << ")" << endl;
    }
    cout << "" << pairs.size() << endl;
}
