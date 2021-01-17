#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <cmath>
#include <iostream>

using namespace std;

#include "binary_tree.hpp"
#include "is_balanced.ipp"
#include "traverse.ipp"
#include "data.ipp"

int main()
{
    for (auto const & [i,v] : traverse_recursive(binary_tree_1())) {
        cout << i << ":";
        for (auto const * n : v) {
            cout << (*n);
        }
        cout << endl;
    }

    for (auto const & [i,v] : traverse_iterative(binary_tree_1())) {
        cout << i << ":";
        for (auto const * n : v) {
            cout << (*n);
        }
        cout << endl;
    }

    for (auto const & n : search<order::pre>(binary_tree_1())) cout << (*n); cout << endl;
    for (auto const & n : search<order::btw>(binary_tree_1())) cout << (*n); cout << endl;
    for (auto const & n : search<order::pos>(binary_tree_1())) cout << (*n); cout << endl;

    cout << "balanced: " << is_balanced(binary_tree_1()) << endl;
}

