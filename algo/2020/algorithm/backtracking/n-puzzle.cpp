#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

#include "board.hpp"
#include "n-puzzle.hpp"
#include "distance.ipp"
#include "n-puzzle.ipp"

int main()
{
    for (int i = 0; i < 10; i++)
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
    1,i).explore();
}

