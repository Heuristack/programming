#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
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
    char value = ' ';
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
    auto get(int i, int j) const -> element
    {
        return this->operator[](i).operator[](j);
    }

public:
    auto is_terminal() const -> bool;
};

auto state::is_terminal() const -> bool
{
    set<element> s;

    auto is_line = [](decltype(s) const & s){
        if (s.size() == 1) {
            auto e = s.begin()->value;
            if (e == X || e == O) {
                return true;
            }
        }
        return false;
    };

    for (int i = 0; i < size_m(i); i++) {
        s.clear();
        for (int j = 0; j < size_n(i); j++) {
            s.insert(get(i,j));
        }
        if (is_line(s)) {
//          cout << "row: " << i << endl;
            return true;
        }
    }

    for (int j = 0; j < size_n(j); j++) {
        s.clear();
        for (int i = 0; i < size_m(j); i++) {
            s.insert(get(i,j));
        }
        if (is_line(s)) {
//          cout << "col: " << j << endl;
            return true;
        }
    }

    s.clear();
    for (int i = 0; i < size_m(i); i++) {
        for (int j = 0; j < size_n(i); j++) {
            if (i == j) {
                s.insert(get(i,j));
            }
        }
    }
    if (is_line(s)) {
//      cout << "diag+: " << endl;
        return true;
    }

    s.clear();
    for (int i = 0; i < size_m(i); i++) {
        for (int j = 0; j < size_n(i); j++) {
            if (i + j == size_m(i) - 1) {
                s.insert(get(i,j));
            }
        }
    }
    if (is_line(s)) {
//      cout << "diag-: " << endl;
        return true;
    }

    return false;
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
      {X,X,O},
      {X,O,O},
      {O,O,E},
    };
    cout << s;
    cout << s.is_terminal() << endl;
}

