#include <algorithm>
#include <vector>
#include <limits>
#include <iostream>

using namespace std;

#include "board.hpp"
#include "n-queens.ipp"

int main()
{
    cout << explore(node(8));
    cout << endl;
}

