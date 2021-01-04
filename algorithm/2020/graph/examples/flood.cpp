#include "board/board.h"
#include "tree.h"

enum color { B = 0, W = 1 };

class element
{
public:
    element(color c) : c(c) {}
    element() = default;

public:
    color c = B;
};

auto operator << (ostream & s, element const & e) -> ostream &
{
    return s << static_cast<int>(e.c);
}

class flood_tree : public tree<node<position>,edge<position>>
{
public:
    using board_type = board<element>;

public:
    flood_tree(int m, int n) : flood_board(m,n) {}
    flood_tree(int n = 10) : flood_tree(n,n) {}
    flood_tree(board_type const & b) : flood_board(b) {}

public:
    auto operator[](node_type const & n) -> set_type<edge_type> override
    {
        set_type<edge_type> edges;
        for (auto [i,j] : generate_adjancents(n.v.i,n.v.j,flood_board.size_m(),flood_board.size_n())) {
            if (flood_board.get(n.v.i,n.v.j).c == flood_board.get(i,j).c) {
                edges.insert(edge_type{n.v, position(i,j)});
            }
        }
        return edges;
    }

    static auto generate_adjancents(int i, int j, int m, int n) -> vector<pair<int,int>>
    {
        vector<pair<int,int>> v;
        for (auto [p,q] : vector<pair<int,int>>{{i-1,j},{i+1,j},{i,j-1},{i,j+1}}) {
            if ((0 <= p) && (p < m) && (0 <= q) && (q < n)) {
                v.emplace_back(p,q);
            }
        }
        return v;
    }

public:
    auto flood_fill(position const & p) -> void
    {
        typename flood_tree::node_type n(p);
        vector<position> positions_to_fill;
        auto v = [&positions_to_fill](auto const & n){
            if (n.s == status::processed) {
                positions_to_fill.emplace_back(n.v.i,n.v.j);
            }
        };
        search<container<strategies::BFS>::type>(*this,n,v);
        for (auto p : positions_to_fill) {
            flap(p);
        }
    }

    auto flap(position const & p) -> void
    {
        color flapped = B;
        switch (flood_board.get(p.i,p.j).c) {
            case color::B : flapped = W; break;
            case color::W : flapped = B; break;
        }
        flood_board.get(p.i,p.j) = flapped;
    }

public:
    board_type flood_board;
};

int main()
{
    typename flood_tree::board_type initial_board {
        {B,W,B,W,W,W,B,B,B,B},
        {W,W,B,W,W,B,W,W,B,B},
        {B,B,B,W,W,B,B,W,B,B},
        {W,B,W,B,B,B,B,W,B,W},
        {B,W,B,W,W,W,W,B,W,W},
        {B,W,B,W,W,B,W,B,B,B},
        {W,W,W,W,B,W,B,W,W,B},
        {B,W,B,W,B,W,B,W,W,W},
        {B,W,B,B,W,W,W,B,B,B},
        {W,W,W,W,W,W,W,B,B,W},
    };
    flood_tree flood(initial_board);
    cout << flood.flood_board << endl;
    flood.flood_fill({5,4});
    cout << flood.flood_board << endl;
    flood.flood_fill({3,6});
    cout << flood.flood_board << endl;
}

