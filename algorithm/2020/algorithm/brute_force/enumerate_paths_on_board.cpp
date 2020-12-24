#include <iostream>
#include <optional>
#include <vector>
#include <set>

using namespace std;

#include "state_space_model.hpp"
#include "enumerate_paths_on_board.ipp"

int main()
{
    board b(5,5);
    cout << b.explore({0,0},{4,4}) << endl;
    for (auto const & s : b.states) cout << s << endl;
    cout << b.states.size() << endl;
}

