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
    typedef heuristic<distance> heuristic_type;
public:
    puzzle(distance d, node i, node g, double a, double b)
    : h(d,i,g,a,b) {}

public:
    auto explore() -> bool { return explore(h.i); }
    auto explore(node const & e) -> bool;
    auto search(node const & e) -> bool;

public:
    bool is_goal(node const & e) { return h.g == e; }

public:
    heuristic_type h;
    vector<node> path;
    vector<node> close;
};

template <typename distance>
auto puzzle<distance>::explore(node const & e) -> bool
{
    close.push_back(e);
    path.push_back(e);
    if (is_goal(e)) {
//      cout << path.back();
        cout << path.size();
        cout << endl;
        return 1;
    }
    for (auto const & n : generate(e,h)) {
        if (find(begin(close),end(close),n) != end(close))
            continue;
        if (explore(n)) return 1;
    }
    path.pop_back();
    return 0;
}

