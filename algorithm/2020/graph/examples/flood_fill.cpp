#include "tree.h"
#include "board/board.hpp"

class element
{
public:
    enum color { B = 0, W = 1 };
public:
    color c = B;
};

auto operator << (ostream & s, element const & e) -> ostream &
{
    return s << static_cast<int>(e.c);
}

int main()
{
    board<element> b(10,10);
    cout << b;
}

