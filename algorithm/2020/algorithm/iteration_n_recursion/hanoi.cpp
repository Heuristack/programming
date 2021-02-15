#include <iostream>
#include <utility>
#include <vector>
#include <array>
#include <stack>

using namespace std;

auto generate(array<stack<int>,3> & pegs, int n, int a, int b, int c, vector<pair<int,int>> & steps) -> void
{
    if (n > 0) {
        generate(pegs, n-1, a,c,b, steps);
        pegs[b].push(pegs[a].top());
        pegs[a].pop();
        steps.emplace_back(a,b);
        generate(pegs, n-1, c,b,a, steps);
    }
}

int main()
{
    constexpr int plates_num = 5;
    array<stack<int>,3> pegs;
    vector<pair<int,int>> steps;
    for (int i = plates_num; i >= 1; i--) {
        pegs[0].push(i);
    }
    generate(pegs,plates_num,0,1,2,steps);
    for (auto [p,q] : steps) {
        cout << "[" << p << "->" << q << "]" << endl;
    }
}

