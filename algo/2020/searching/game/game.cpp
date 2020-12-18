#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <utility>
#include <initializer_list>

using namespace std;

#include "board.hpp"

enum noughts_n_crosses { E = 'E', X = 'X', O = 'O' };

class element
{
public:
    element(char v): value(v) {}
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
    auto get(int i, int j) const -> element { return this->operator[](i).operator[](j); }

public:
    auto terminal_test() const -> pair<bool,int>;
    auto is_terminal() -> bool;
    auto utility() -> int;

private:
    bool is_terminal_{};
    int utility_{};
};

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

auto operator << (ostream & s, state const & b) -> ostream &
{
    for (int i = 0; i < b.size_m(i); i++) {
    for (int j = 0; j < b.size_n(i); j++) {
        s << b[i][j] << " ";
    }   s << "\n";
    }
    return s;
}

int main()
{
    state s
    {
      {O,X,O},
      {X,X,O},
      {O,O,X},
    };
    cout << s;
    cout << "is terminal = " << s.is_terminal() << "; utility = " << s.utility() << ";" << endl;
}

