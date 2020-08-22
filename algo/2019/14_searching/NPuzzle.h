#ifndef N_PUZZLE_H
#define N_PUZZLE_H

#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

enum class Direction
{
    Up, Down, Left, Right,
    U = Up, D = Down, L = Left, R = Right
};

template <typename T = int>
struct NPuzzle
{
public:
    NPuzzle(unsigned int nxn = 3): n{nxn}
    {
        resize(n);
        for_each_tile([](auto & tile){
                tile = {};
        });
    }

    NPuzzle(NPuzzle const & that): n{that.n}
    {
        resize(that.n);
        for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            board[i][j] = that.board[i][j];
        }
        }
    }

    auto resize(unsigned int nxn) -> void
    {
        n = nxn;
        board.resize(n);
        for (auto & row : board) row.resize(n);
    }

public:
    template <typename Function>
    auto for_each_tile(Function f) -> void
    {
        for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            f(board[i][j]);
        }
        }
    }

    template <typename Function>
    auto for_each_tile(NPuzzle & that, Function f) const -> void
    {
        for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            f(board[i][j], that.board[i][j]);
        }
        }
    }

    template <typename Predicate>
    auto all_tile_of(Predicate p) const -> bool
    {
        for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            if (p(board[i][j])) continue;
            else return false;
        }
        }
        return true;
    }

    template <typename Predicate>
    auto all_tile_of(NPuzzle const & that, Predicate p) const -> bool
    {
        for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            if (p(board[i][j], that.board[i][j])) continue;
            else return false;
        }
        }
        return true;
    }

public:
    auto empty() const -> bool
    {
        return all_tile_of([](auto const & tile){
            return tile == T{};
        });
    }

    auto equal(NPuzzle const & that) const -> bool
    {
        return all_tile_of(that, [](auto const & this_tile, auto const & that_tile){
            return this_tile == that_tile;
        });
    }

    NPuzzle clone() const
    {
        return NPuzzle(*this);
    }

    NPuzzle goal() const
    {
        NPuzzle g;
        auto k = 1;
        for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            if (k != n*n) g.board[i][j] = k++;
            else g.board[i][j] = 0;
        }
        }
        return g;
    }

    auto is_goal() const -> bool
    {
        auto k = 1;
        for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            if (k != n*n) { if (board[i][j] != k++) return 0; }
            else { if (board[i][j] != 0) return 0; }
        }
        }
        return 1;
    }

    auto locate(T target = {}) const -> pair<T,T>
    {
        for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            if (board[i][j] == target) {
                return {i,j};
            }
        }
        }
        return {{},{}};
    }

    auto move(Direction d) -> bool
    {
        auto [i,j] = locate();
        if (Direction::U == d) { if (i == 1-1) return 0; else swap(board[i][j],board[i-1][j]); }
        if (Direction::D == d) { if (i == n-1) return 0; else swap(board[i][j],board[i+1][j]); }
        if (Direction::L == d) { if (j == 1-1) return 0; else swap(board[i][j],board[i][j-1]); }
        if (Direction::R == d) { if (j == n-1) return 0; else swap(board[i][j],board[i][j+1]); }
        return 1;
    }

    auto clone_and_move(Direction d) -> NPuzzle
    {
        if (empty()) return {};
        auto next = clone();
        auto [i,j] = locate();
        switch(d) {
            case Direction::U: if (i != 1-1) swap(next.board[i][j],next.board[i-1][j]); break;
            case Direction::D: if (i != n-1) swap(next.board[i][j],next.board[i+1][j]); break;
            case Direction::L: if (j != 1-1) swap(next.board[i][j],next.board[i][j-1]); break;
            case Direction::R: if (j != n-1) swap(next.board[i][j],next.board[i][j+1]); break;
            default: break;
        }
        return next;
    }

    auto generate() -> vector<NPuzzle>
    {
        vector<NPuzzle> v;
        for (auto direction : {Direction::R,Direction::D,Direction::L,Direction::U}) {
            if (auto next = clone_and_move(direction); !equal(next)) {
                v.push_back(next);
            }
        }
        return v;
    }

public:
    auto hamming() const -> int
    {
        auto v = 0;
        auto g = goal();
        for_each_tile(g,[&v](auto const & this_tile, auto const & that_tile){
            if (that_tile != 0) {
                v += (this_tile != that_tile);
            }
        });
        return v;
    }

    auto manhattan() const -> int
    {
        auto v = 0;
        auto g = goal();
        for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            auto [i0,j0] = locate(g.board[i][j]);
            if (g.board[i][j]) {
                v += abs(i-i0) + abs(j-j0);
            }
        }
        }
        return v;
    }

public:
    friend auto dfs(NPuzzle & node, vector<NPuzzle> & solution) -> void
    {
        static bool resolve = 0;
        static vector<NPuzzle> closed;

        closed.push_back(node);
        cout << node;

        if (node.is_goal()) {
            resolve = 1;
        }
        if (resolve) {
            solution.push_back(node);
            return ;
        }
        auto generation = node.generate();
        cout << generation << endl;
        for (auto & next : generation) {
            if (resolve) {
                return ;
            }

            solution.push_back(node);
            if (find(begin(closed),end(closed),next) == end(closed)) {
                dfs(next,solution);
            }
            if (resolve) {
                return;
            }
            else {
                solution.pop_back();
            }
        }
    }

    friend auto pure_heuristic_search(NPuzzle & node, vector<NPuzzle> & solution) -> void
    {
        vector<NPuzzle> closed;
        closed.push_back(node);
        auto order = [](NPuzzle const & a, NPuzzle const & b){
            return a.hamming() > b .hamming();
        };
        priority_queue<NPuzzle, vector<NPuzzle>, decltype(order)> open(order);
        open.push(node);
        while (!open.empty()) {
            auto u = open.top();
            open.pop();
            solution.push_back(u);
            if (u.is_goal()) {
                return;
            }
            auto generation = u.generate();
            for (auto const & v : generation) {
                if (find(begin(closed),end(closed),v) == closed.end()) {
                    open.push(v);
                }
            }
            closed.push_back(u);
        }
    }

public:
    vector<vector<T>> board;
    unsigned int n;

public:
    friend auto operator == (NPuzzle const & a, NPuzzle const & b) -> bool
    {
        return a.equal(b);
    }

    friend auto operator >> (istream & s, NPuzzle & puzzle) -> istream &
    {
        s >> puzzle.n;
        puzzle.resize(puzzle.n);
        for (auto i = 0; i < puzzle.n; i++) {
        for (auto j = 0; j < puzzle.n; j++) {
            s >> puzzle.board[i][j];
        }
        }
        return s;
    }
    friend auto operator << (ostream & s, NPuzzle const & puzzle) -> ostream &
    {
        for (auto i = 0; i < puzzle.n; i++) {
        for (auto j = 0; j < puzzle.n; j++) {
            s << puzzle.board[i][j] << " ";
        }
        s << "\n";
        }
        return s;
    }
    friend auto operator << (ostream & s, vector<NPuzzle> const & v) -> ostream &
    {
        if (v.empty()) return s;
        auto n = v[0].n;
        for (auto i = 0; i < n; i++) {
        for (auto k = 0; k < v.size(); k++) {
        for (auto j = 0; j < n; j++) {
            s << v[k].board[i][j] << " ";
        }
        s << "  ";
        }
        s << "\n";
        }
        return s;
    }
};

#endif

