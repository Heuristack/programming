#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

using namespace std;

#include "board.hpp"

class state : public board<char>
{
public:
    using board_type = board<char>;
    using board_type::board_type;
};

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
      {'X','X','O'},
      {'X','X','O'},
      {'X','X','X'},
    };
    cout << s;
}

