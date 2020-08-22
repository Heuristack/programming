#include "NPuzzle.h"
#include <iostream>
using namespace std;

int main()
{
    NPuzzle puzzle(3);
    cin  >> puzzle;

    vector<NPuzzle<int>> solution;
    pure_heuristic_search(puzzle,solution);
    for (auto s : solution) {
        cout << s;
    }

#if 0
    cout << puzzle.hamming() << endl;
    cout << puzzle.manhattan() << endl;

    vector<NPuzzle<int>> solution;
    dfs(puzzle, solution);
    cout << solution.size() << endl;
    for (auto s : solution) {
        cout << s;
        cout << count(begin(solution),end(solution),s) << endl;
    }

    cout << "Puzzle: " << endl;
    cout << puzzle;

    NPuzzle x(3);
    cout << x;
    x = puzzle;
    cout << x;

    auto clone = puzzle.clone();
    cout << clone;
    cout << (puzzle == clone) << endl;
    cout << clone.goal();

    vector<NPuzzle<int>> v;
    v.push_back(puzzle);
    v.push_back(clone);
    v.push_back(clone.goal());
    cout << v;

    cout << (find(begin(v),end(v),puzzle) == end(v)) << endl;
    auto i = find(begin(v),end(v),puzzle);
    cout << *i;
    vector<NPuzzle<int>> solution;
    dfs(puzzle, solution);
    cout << "solution:\n" << solution << endl;
    cout << endl;
#endif
}

