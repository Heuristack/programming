#include "structure/binary_tree/binary_tree.h"

int main()
{
    for (auto const & [i,v] : traverse(binary_tree_1())) {
        cout << i << ":";
        for (auto const * n : v) {
            cout << (*n);
        }
        cout << endl;
    }
}

