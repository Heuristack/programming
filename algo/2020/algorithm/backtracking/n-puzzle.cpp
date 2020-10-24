#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

#include "board.hpp"
#include "n-puzzle.hpp"
#include "n-puzzle.ipp"
#include "heuristics.ipp"

template <typename distance>
class puzzle
{
public:
    puzzle(distance d, node i, node g, double a, double b)
    : h(d,i,g,a,b) {}

public:
    auto explore() -> bool { return ::explore(h.i,h); }

public:
    heuristic<distance> h;
};

int main()
{
    puzzle(manhattan,
    make({
        {8,1,3},
        {4,0,2},
        {7,6,5},
    }),
    make({
        {0,1,2},
        {3,4,5},
        {6,7,8},
    }),
    1,5).explore();
}

