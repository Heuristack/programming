#include "implicit_graph.h"
#include "algorithm/search.hpp"
#include <iostream>
#include "board.hpp"

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

class position
{
public:
    position(int i, int j) : i(i), j(j) {}
public:
    bool operator < (position const & that) { return tie(i,j) < tie(that.i,that.j); }
public:
    int i = 0;
    int j = 0;
};

auto operator << (ostream & s, position const & p) -> ostream &
{
    return s << "(" << p.i << "," << p.j << ")";
}

int main()
{
    board<element> b(10,10);
    cout << b;
}

