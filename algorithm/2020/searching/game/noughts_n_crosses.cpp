#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <utility>
#include <limits>
#include <iostream>
#include <initializer_list>

using namespace std;

#include "board/board.hpp"

enum noughts_n_crosses { E = 'E', X = 'X', O = 'O' };

class element
{
public:
    element(char v): value(v) {}
    element() = default;

public:
    bool operator < (element const & that) const { return this->value < that.value; }

public:
    char value = E;
};

auto operator << (ostream & s, element const & e) -> ostream &
{
    return s << e.value;
}

class state : public board<element>
{
public:
    using board_type = board<element>;
    using board_type::board_type;

public:
    state(): board_type(3) {}

public:
    auto get(int i, int j) const -> element const & { return this->operator[](i).operator[](j); }
    auto get(int i, int j) -> element & { return const_cast<element&>(const_cast<state const *>(this)->get(i,j)); }

public:
    auto available_positions() const -> vector<position>;
    auto terminal_test() const -> pair<bool,int>;
    auto is_terminal() -> bool;
    auto utility() -> int;

private:
    bool is_terminal_{};
    int utility_{};
};

auto operator << (ostream & s, state const & n) -> ostream &
{
    for (int i = 0; i < n.size_m(); i++) {
        for (int j = 0; j < n.size_n(); j++) {
            s << n[i][j] << " ";
        }   s << "\n";
    }
    return s;
}

auto state::available_positions() const -> vector<position>
{
    vector<position> moves;
    for (int i = 0; i < size_m(); i++) {
    for (int j = 0; j < size_n(); j++) {
        if (get(i,j).value == E) {
            moves.emplace_back(i,j);
        }
    }
    }
    return moves;
}

auto state::terminal_test() const -> pair<bool,int>
{
    set<element> line;
    int value = 0;

    auto is_lined_up = [&line,&value](){
        if (line.size() == 1) {
            if (auto e = line.begin()->value; e != E) {
                if (e == X) value = +1;
                if (e == O) value = -1;
                return true;
            }
        }
        return false;
    };

    // note : rows
    for (int i = 0; i < size_m(); i++) {
        line.clear();
        for (int j = 0; j < size_n(); j++) {
            line.insert(get(i,j));
        }
        if (is_lined_up()) {
//          cout << "row: " << i << endl;
            return {true,value};
        }
    }

    // note : cols
    for (int j = 0; j < size_n(); j++) {
        line.clear();
        for (int i = 0; i < size_m(); i++) {
            line.insert(get(i,j));
        }
        if (is_lined_up()) {
//          cout << "col: " << j << endl;
            return {true,value};
        }
    }

    // note : diag+
    line.clear();
    for (int i = 0; i < size_m(); i++) {
        for (int j = 0; j < size_n(); j++) {
            if (i == j) {
                line.insert(get(i,j));
            }
        }
    }
    if (is_lined_up()) {
//      cout << "diag+: " << endl;
        return {true,value};
    }

    // note : diag-
    line.clear();
    for (int i = 0; i < size_m(); i++) {
        for (int j = 0; j < size_n(); j++) {
            if (i + j == size_m(i) - 1) {
                line.insert(get(i,j));
            }
        }
    }
    if (is_lined_up()) {
//      cout << "diag-: " << endl;
        return {true,value};
    }

    // note : all filled
    for (int i = 0; i < size_m(); i++) {
        for (int j = 0; j < size_n(); j++) {
            if (get(i,j).value == E) {
                return {false,value};
            }
        }
    }

//  cout << "filled" << endl;
    return {true,value};
}

auto state::is_terminal() -> bool
{
    auto result = terminal_test();
    is_terminal_ = std::get<0>(result);
    utility_ = std::get<1>(result);
    return is_terminal_;
}

auto state::utility() -> int
{
    return utility_;
}

auto minimax_decision(state const & s) -> position;
auto max_value(state s) -> int;
auto min_value(state s) -> int;
auto alpha_beta_search(state const & s) -> position;
auto max_value(state s, int alpha, int beta) -> int;
auto min_value(state s, int alpha, int beta) -> int;

class player
{
public:
    player(string const & n, element const & e): name(n), e(e) {}
    player(element const & e): player("", e) {}

public:
    auto move(state const & s) const -> position;

public:
    string name;
    element e;
};

auto operator << (ostream & s, player const & p) -> ostream &
{
    return s << p.name << "(" << p.e << ")";
}

auto player::move(state const & s) const -> position
{
    // todo : set strategy to player instance, can be different.
    //        should player MIN(O) use the same strategy as MAX(X) ...
    return alpha_beta_search(s);
}

class action
{
public:
    action(player const & who, position const & where): who(who), where(where) {}

public:
    position where;
    player who;
};

auto operator << (ostream & s, action const & a) -> ostream &
{
    return s << "[" << a.who << ":" << a.where << "]";
}

auto result(state const & s, action const & a) -> state
{
    state next = s;
    next.get(a.where.i, a.where.j) = a.who.e;
    return next;
}

class game
{
public:
    game(initializer_list<player> players): players(players) {}

public:
    auto move(action const & a) -> void;
    auto play() -> int;

public:
    vector<player> players;
    state current_state;
};

auto operator << (ostream & s, game const & g) -> ostream &
{
    for (auto player : g.players) {
        s << player << "\n";
    }
    s << g.current_state;
    return s;
}

auto game::move(action const & a) -> void
{
    current_state = result(current_state, a);
}

auto game::play() -> int
{
    for (;;) {
    for (auto const & p : players) {
        auto a = action(p,p.move(current_state));
        cout << a << endl;
        move(a);
        if (current_state.is_terminal()) {
            return current_state.utility();
        }
    }
    }
    return 0;
}

auto minimax_decision(state const & s) -> position
{
    int max = numeric_limits<int>::min();
    position max_position;
    for (auto const & p : s.available_positions()) {
        if (int min = min_value(result(s,action(element(X),p))); min > max) {
            max = min;
            max_position = p;
        }
    }
    return max_position;
}

auto max_value(state s) -> int
{
    if (s.is_terminal()) return s.utility();
    int val = numeric_limits<int>::min();
    for (auto const & p : s.available_positions()) {
        val = max(val,min_value(result(s,action(element(X),p))));
    }
    return val;
}

auto min_value(state s) -> int
{
    if (s.is_terminal()) return s.utility();
    int val = numeric_limits<int>::max();
    for (auto const & p : s.available_positions()) {
        val = min(val,max_value(result(s,action(element(O),p))));
    }
    return val;
}

auto alpha_beta_search(state const & s) -> position
{
    int max = numeric_limits<int>::min();
    position max_position;
    for (auto const & p : s.available_positions()) {
        if (int min = min_value(result(s,action(element(X),p)), numeric_limits<int>::min(),numeric_limits<int>::max()); min > max) {
            max = min;
            max_position = p;
        }
    }
    return max_position;
}

auto max_value(state s, int alpha, int beta) -> int
{
    if (s.is_terminal()) return s.utility();
    int val = numeric_limits<int>::min();
    for (auto const & p : s.available_positions()) {
        val = max(val,min_value(result(s,action(element(X),p)),alpha,beta));
        if (val >= beta) return val;
        alpha = max(alpha,val);
    }
    return val;
}

auto min_value(state s, int alpha, int beta) -> int
{
    if (s.is_terminal()) return s.utility();
    int val = numeric_limits<int>::max();
    for (auto const & p : s.available_positions()) {
        val = min(val,max_value(result(s,action(element(O),p)),alpha,beta));
        if (val <= alpha) return val;
        beta = min(beta,val);
    }
    return val;
}

int main()
{
    game g({player("MAX",X),player("MIN",O)});
    cout << g.play() << endl;
    cout << g.current_state;
}

