#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

#include "board.hpp"
#include "n-puzzle.hpp"
#include "distance.ipp"
#include "n-puzzle.ipp"
#include "n-puzzle_explore.ipp"
#include "n-puzzle_search.ipp"

int main()
{
    for (int i = 1; i < 10; i++) {
        cout << i << ": ";
        puzzle sliding(manhattan,
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
        1,i);
        sliding.reset().explore();
        cout << ":";
        sliding.reset().search();
        cout << endl;
    }
}

