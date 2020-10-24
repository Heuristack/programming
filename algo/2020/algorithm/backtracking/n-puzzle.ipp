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

template <typename heuristic>
auto explore(node const & e, heuristic h) -> bool
{
    static vector<node> path = {e};
    static vector<node> c;
    c.push_back(e);
    if (is_goal(e)) {
        cout << path;
        return 1;
    }
    for (auto const & n : generate(e,h)) {
        if (find(begin(c),end(c),n) != end(c))
            continue;
        path.push_back(n);
        if (explore(n,h)) return 1;
        path.pop_back();
    }
    return 0;
}

