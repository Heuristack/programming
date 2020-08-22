#include <iostream>
#include <vector>

using namespace std;

struct state
{
    state(int i, int j) : i(i), j(j) {}
    state() : state(0,0) {}

    int i = 0;
    int j = 0;
};

ostream & operator << (ostream & strm, state const & s)
{
    return strm << "(" << s.i << "," << s.j << ")";
}

struct space
{
    space(int m, int n) : m(m), n(n) {}

    auto generate_next_states(state s) -> vector<state>
    {
        vector<state> next_states;
        if (s.i < m - 1) next_states.emplace_back(s.i + 1, s.j);
        if (s.j < n - 1) next_states.emplace_back(s.i, s.j + 1);
        return next_states;
    }

    auto dfs(state s) -> int
    {
        path.push_back(s);

        if (s.i == m -1 && s.j == n-1) {
            for (state const & n : path) cout << n;
            cout << endl;
            w++;
        }

        for (state const & n : generate_next_states(s)) {
            dfs(n);
        }

        path.pop_back();
        return w;
    }

    vector<state> path;

    int m = 0;
    int n = 0;
    int w = 0;
};


int main()
{
    cout << space(5,5).dfs(state{0,0});
    cout << endl;
}

