#include "board/board.h"

enum color { B = 0, W = 1, G = 2 };

auto to_string(enum color c) -> string
{
    string s;
    switch (c) {
    case B : s = 'B'; break;
    case W : s = 'W'; break;
    case G : s = 'G'; break;
    }
    return s;
}

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
    return s << to_string(e.c);
}

class region : public board<element>
{
public:
    using board_type = board<element>;
    using board_type::board;

public:
    auto boundaries(enum color c = W) -> vector<position>
    {
        vector<position> v;
        auto add_if = [&v,c,this](int i, int j) {
            if (get(i,j).c == c) {
                v.emplace_back(i,j);
            }
        };
        for (int i = 0; i < size_m(); i++) {
            add_if(i,0);
            add_if(i,size_n()-1);
        }
        for (int j = 0; j < size_n(); j++) {
            add_if(0,j);
            add_if(size_m()-1,j);
        }
        return v;
    }

    template <typename return_type = vector<position>>
    auto generate(position const & p, enum color c = W) -> return_type
    {
        return_type v;
        for (auto q : return_type{{p.i-1,p.j},{p.i+1,p.j},{p.i,p.j-1},{p.i,p.j+1}}) {
            if ((0 <= q.i) && (q.i < size_m()) && (0 <= q.j) && (q.j < size_n())) {
                if (get(q.i,q.j).c == c) {
                    v.push_back(q);
                }
            }
        }
        return v;
    }

public:
    auto explore(position const & p, enum color c = W) -> void
    {
        if (get(p.i,p.j).c == c)
            get(p.i,p.j).c = G;
        for (auto q : generate(p)) {
            explore(q,c);
        }
    }

    auto enclose() -> void
    {
        for (auto p : boundaries()) {
            explore(p);
        }
        for (int i = 0; i < size_m(); i++) {
        for (int j = 0; j < size_n(); j++) {
            if (get(i,j).c == W)
                get(i,j).c = B;
            if (get(i,j).c == G)
                get(i,j).c = W;
        }
        }
    }
};

int main()
{
    region r {
      {B,B,B,B},
      {W,B,W,B},
      {B,W,W,B},
      {B,B,B,B},
    };
    cout << r << endl;
    r.enclose();
    cout << r << endl;
}

