Sliding-Puzzle: 2x3
-------------------
`Not Finished Yet`

```C++
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    using Board = vector<vector<int>>;

    int slidingPuzzle(vector<vector<int>>& board) {
        vector<Board> solution;
        heuristic_search(board, solution);
        if (solution.size() == 0) return -1;
        else return static_cast<int>(solution.size());
    }

    auto is_goal(Board & board) -> bool
    {
        auto k = 1;
        for (auto i = 0; i < M; i++) {
            for (auto j = 0; j < N; j++) {
                if (i == M-1 && j == N-1) k = 0;
                if (board[i][j] == k++) continue;
                else return false;
            }
        }
        return true;
    }

    auto locate(Board & board) -> pair<int,int>
    {
        for (auto i = 0; i < M; i++) {
            for (auto j = 0; j < N; j++) {
                if (board[i][j] == 0) {
                    return {i,j};
                }
            }
        }
        return {M,N};
    }

    enum class Direction { Up, Down, Left, Right, U = Up, D = Down, L = Left, R = Right};
    auto move(Board & board, Direction d) -> Board
    {
        Board next(board);
        auto position = locate(next);
        auto i = position.first;
        auto j = position.second;
        if (Direction::U == d) { if (i != 1-1) { swap(next[i][j],next[i-1][j]); } }
        if (Direction::D == d) { if (i != M-1) { swap(next[i][j],next[i+1][j]); } }
        if (Direction::L == d) { if (j != 1-1) { swap(next[i][j],next[i][j-1]); } }
        if (Direction::R == d) { if (j != N-1) { swap(next[i][j],next[i][j+1]); } }
        return next;
    }

    auto generate(Board & board) -> vector<Board>
    {
        vector<Board> generation;
        for (auto d : {Direction::R,Direction::D,Direction::L,Direction::U}) {
            auto next = move(board,d);
            if (next != board) {
                generation.push_back(move(board,d));
            }
        }
        return generation;
    }

    auto dfs(Board & board, bool & resolved) -> void
    {
        static vector<Board> closed;
        closed.push_back(board);

        if (is_goal(board)) {
            resolved = true;
            return;
        }

        auto generation = generate(board);
        for (auto next : generation) {
            if (!resolved) {
                if (find(begin(closed),end(closed),next) == closed.end()) {
                    dfs(next,resolved);
                }
            }
        }
    }

    auto heuristic(Board const & board) -> int
    {
        auto v = 0;
        auto k = 1;
        for (auto i = 0; i < M; i++) {
            for (auto j = 0; j < N; j++) {
                if (i == M-1 && j == N-1) k = 0;
                if (board[i][j] != k++) v++;
            }
        }
        return v;
    }

    auto heuristic_search(Board & board, vector<Board> & solution) -> void
    {
        vector<pair<Board,Board>> closed;
        auto order = [this](Board const & a, Board const & b)->bool{ return heuristic(a) > heuristic(b); };
        priority_queue<Board,vector<Board>,decltype(order)> open(order);
        open.push(board);
        while (!open.empty()) {
            auto u = open.top();
            open.pop();
            solution.push_back(u);
            if (is_goal(u)) {
                solution.push_back(u);
                return;
            }
            auto generation = generate(u);
            for (auto & v : generation) {
                if (find(begin(closed),end(closed),make_pair(v,{})) == closed.end()) {
                    open.push(v);
                }
            }
        }
    }

    int M = 2;
    int N = 3;
};

int main()
{
    vector<vector<int>> board = {{4,1,2},{5,0,3}};
    Solution solution;
    cout << solution.slidingPuzzle(board) << endl;
    vector<vector<int>> goal = {{1,2,3},{4,5,0}};
    cout << solution.is_goal(goal) << endl;
}
```

