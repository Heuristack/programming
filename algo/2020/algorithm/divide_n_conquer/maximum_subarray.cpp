#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

#include "kadane.ipp"

int main()
{
    cout << kadane({5,-7,3,5,-2,4,-1}) << endl;
    cout << kadane({-2,1,2}) << endl;
    cout << kadane({-2}) << endl;
}

