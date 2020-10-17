#include <iostream>
#include <optional>
#include <vector>
#include <set>

using namespace std;

template <typename state_t, typename operate_t>
class state_space_model
{
public:
    typedef state_t state_type;
    typedef operate_t operate_type;

public:
    state_space_model(state_type i, state_type g) : init(i), goal(g) {}
    state_space_model() = default;

public:
    virtual auto visit(state_type) -> void {}
    virtual auto next(state_type s, operate_type o) -> optional<state_type> = 0;

    auto expand(state_type s) -> vector<state_type>
    {
        vector<state_type> next_states;
        for (auto const & o : operates) {
            auto n = next(s,o);
            if (n.has_value()) {
                next_states.push_back(n.value());
            }
        }
        return next_states;
    }

public:
    virtual auto search(state_type s) -> void
    {
        visit(s);
        if (s == goal) return;
        for (auto const & s : expand(s)) {
            search(s);
        }
    }

public:
    set<state_type> states;
    set<operate_type> operates;

public:
    state_type init{};
    state_type goal{};
};

struct state
{
    state(int i, int j) : i(i), j(j) {}
    state() : state(0,0) {}

    int i = 0;
    int j = 0;

    bool operator == (state const & that) const { return (this->i == that.i) && (this->j == that.j); }
    bool operator  < (state const & that) const { return (this->i  < that.i) || (this->j  < that.j); }
};
ostream & operator << (ostream & strm, state const & s) { return strm << "(" << s.i << "," << s.j << ")"; }

enum operate { E, S };

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
        if (s == state_type(2,1)) {
            cout << "impossible" << endl;
        }
        if (states.find(s) == states.end()) {
            states.insert(s);
        }

        path.push_back(s);

        if (s == goal) {
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
        init = i;
        goal = g;
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
    cout << b.states.size() << endl;
    for (auto const & s : b.states) cout << s << endl;
    set<state> s;
    s.insert({2,1});
    s.insert({2,1});
    s.insert({2,1});
    cout << s.size() << endl;
}

