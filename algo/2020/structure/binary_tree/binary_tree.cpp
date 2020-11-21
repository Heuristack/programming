#include "binary_tree.h"

int main()
{
    for (auto const & [i,v] : traverse(binary_tree_1())) {
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

