#include <algorithm>
#include <iostream>
#include "board/board.h"

using namespace std;

bool binary_search(board<int> const & a, int k)
{
    int m = a.size_m();
    int n = a.size_n();
    for (int i = 0, j = n-1; i < m && 0 < j;) {
        if (auto e = a.get(i,j); e == k) return 1;
        else if (k < e) { j--; } // eliminate col
        else if (k > e) { i++; } // eliminate row
    }
    return 0;
}

int main()
{
    board<int> b
    {
      {1, 2, 4, 4, 6},
      {1, 5, 5, 9,21},
      {3, 6, 6, 9,22},
      {3, 6, 8,10,24},
      {6, 8, 9,12,25},
      {8,10,12,13,40},
    };
    cout << binary_search(b,7) << endl;
    cout << binary_search(b,8) << endl;
}

