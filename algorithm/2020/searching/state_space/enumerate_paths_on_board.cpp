#include <iostream>
#include <optional>
#include <vector>
#include <set>

using namespace std;

#include "state_space_model.hpp"

struct state
{
    state(int i, int j) : i(i), j(j) {}
    state() : state(0,0) {}

    int i = 0;
    int j = 0;

    bool operator == (state const & that) const { return (this->i == that.i) && (this->j == that.j); }
    bool operator  < (state const & that) const
    {
        if (this->i == that.i) return (this->j < that.j);
        else return (this->i  < that.i);
    }
};
ostream & operator << (ostream & strm, state const & s) { return strm << "(" << s.i << "," << s.j << ")"; }

enum operate{E,S};

class board : public state_space_model<state,operate>
{
public:
    board(int m, int n) : m(m), n(n)
    {
        operates.insert(E);
        operates.insert(S);
    }

public:
    auto next(state_type s, operate_type o) -> optional<state_type> override
    {
        if ((o == E) && (s.i < m-1)) return make_optional<state_type>(s.i + 1, s.j);
        if ((o == S) && (s.j < n-1)) return make_optional<state_type>(s.i, s.j + 1);
        return nullopt;
    }

public:
    auto backtrack(state_type s) -> int
    {
        states.insert(s);
        path.push_back(s);
        if (is_goal(s)) {
            for (auto const & s : path) {
                cout << s;
            }
            cout << endl;
            w++;
        }
        for (auto const & s : expand(s)) {
            backtrack(s);
        }
        path.pop_back();
        return w;
    }

    auto explore(state_type i, state_type g) -> int
    {
        // note : explicit goal state instead of goal condition -> bidirection search
        init = i; goal = g;
        return backtrack(init);
    }

public:
    vector<state_type> path;

public:
    int m = 0;
    int n = 0;
    int w = 0;
};


int main()
{
    board b(5,5);
    cout << b.explore({0,0},{4,4}) << endl;
    for (auto const & s : b.states) cout << s << endl;
    cout << b.states.size() << endl;
}

