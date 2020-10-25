auto generate(int i, int j, int n) -> vector<pair<int,int>>
{
    vector<pair<int,int>> v;
    for (auto [p,q] : vector<pair<int,int>>{{i-1,j},{i+1,j},{i,j-1},{i,j+1}}) {
        if ((0 <= p) && (p < n) && (0 <= q) && (q < n)) {
            v.emplace_back(p,q);
        }
    }
    return v;
}

template <typename heuristic>
auto generate(node const & b, heuristic h) -> vector<node>
{
    vector<node> v;
    auto [i,j] = locate(b);
    for (auto [p,q] : generate(i,j,b.n)) {
        node n(b);
        swap(n[i][j],n[p][q]);
        v.push_back(n);
    }
    if (!h) return v;
    sort(begin(v),end(v),[h](auto const & a, auto const & b) {
        return h(a) < h(b);
    });
    return v;
}

template <typename distance>
class puzzle
{
public:
    typedef puzzle<distance> this_type;
    typedef heuristic<distance> heuristic_type;
public:
    puzzle(distance d, node i, node g, double a, double b)
    : h(d,i,g,a,b) {}
    auto reset() -> this_type & { path.clear(); close.clear(); return *this; }

public:
    auto explore() -> bool { return explore(h.i); }
    auto explore(node const & e) -> bool;
    auto search() -> bool { return search(h.i); }
    auto search(node const & e) -> bool;

public:
    bool is_goal(node const & e) { return h.g == e; }

public:
    heuristic_type h;
    vector<node> path;
    vector<node> close;
};

