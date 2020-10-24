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
#include "n-puzzle_heuristics.ipp"

int main()
{
    auto puzzle = make({
        {8,1,3},
        {4,0,2},
        {7,6,5},
    });
    explore(puzzle,nullheuristic);
}

