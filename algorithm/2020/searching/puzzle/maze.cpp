#include "board/board.h"

using namespace std;

class maze : public board<bool>
{
public:
    using board_type = board<bool>;
    using board_type::board;

public:
    template <typename return_type = vector<pair<int,int>>>
    auto generate(int i, int j, int m, int n) -> return_type
    {
        return_type adjacents;
        for (auto [p,q] : return_type{{i-1,j},{i+1,j},{i,j-1},{i,j+1}}) {
            if ((0 <= p) && (p < m) && (0 <= q) && (q < n)) {
                if (!this->operator[](p).operator[](q)) {
                    adjacents.emplace_back(p,q);
                }
            }
        }
        return adjacents;
    }

public:
    auto search(position s, position e, vector<position> & path) -> bool
    {
        if (s == e) return true;
        for (auto [p,q] : generate(s.i,s.j,size_m(s.i),size_n(s.i))) {
            this->operator[](p).operator[](q) = true;
            path.emplace_back(p,q);
            if (search(position(p,q),e,path)) {
                return true;
            }
            path.pop_back();
        }
        return false;
    }

    auto search(position s, position e)
    {
        vector<position> path;
        path.push_back(s);
        this->operator[](s.i).operator[](s.j) = true;
        if (!search(s,e,path)) {
            path.pop_back();
        }
        reverse(path.begin(),path.end());
        return path;
    }
};

int main()
{
    maze m {
        {1,0,0,0,0,0,1,1,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {1,0,1,0,0,1,1,0,1,1},
        {0,0,0,1,1,1,0,0,1,0},
        {0,1,1,0,0,0,0,0,0,0},
        {0,1,1,0,0,1,0,1,1,0},
        {0,0,0,0,1,0,0,0,0,0},
        {1,0,1,0,1,0,1,0,0,0},
        {1,0,1,1,0,0,0,1,1,1},
        {0,0,0,0,0,0,0,1,1,0},
    };
    cout << m;
    for (auto p : m.search(position(9,0),position(0,9))) {
       cout << p;
    }
}
