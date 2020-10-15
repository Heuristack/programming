#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

#include "binary_tree.hpp"
#include "is_balanced.ipp"
#include "traverse.ipp"
#include "data.ipp"

int main()
{
    for (auto const & [i,v] : traverse(binary_tree_1())) {
        cout << i << ":";
        for (auto const * n : v) {
            cout << (*n);
        }
        cout << endl;
    }
    cout << is_balanced(binary_tree_1()) << endl;
}

