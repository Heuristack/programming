class node : public board<int>
{
public:
    typedef board<int> base_type;
public:
    node(int n) : base_type(n) {}
    node() = default;
};

ostream & operator << (ostream & s, vector<node> const & v)
{
    for (auto const & e : v) {
        s << e;
    }
    return s;
}

auto make(vector<vector<int>> m) -> node
{
    node b(m.size());
    for (int i = 0; i < b.n; i++) {
    for (int j = 0; j < b.n; j++) {
        b[i][j] = m[i][j];
    }
    }
    return b;
}

auto locate(node const & b, int x = 0) -> pair<int,int>
{
    for (int i = 0; i < b.n; i++) {
    for (int j = 0; j < b.n; j++) {
        if (b[i][j] == x) {
            return {i,j};
        }
    }
    }
    return {0,0};
}

auto serialize(node const & n) -> vector<int>
{
    vector<int> v;
    for (int i = 0; i < n.n; i++) {
    for (int j = 0; j < n.n; j++) {
        v.push_back(n[i][j]);
    }
    }
    return v;
}

bool operator < (node const & a, node const & b)
{
    auto va = serialize(a);
    auto vb = serialize(b);
    return lexicographical_compare(
        begin(va),end(va),
        begin(vb),end(vb)
    );
}

template <typename distance>
class heuristic
{
public:
    heuristic(distance d, node i, node g, double a, double b)
    : d(d),i(i),g(g),a(a),b(b) {}

public:
    double operator()(node const & e) const { return a * d(e,i) + b * d(e,g); }
    operator bool () const { return d != nullptr; }

public:
    distance d = nullptr;
    node i;
    node g;
    double a;
    double b;
};

auto hamming(node const & a, node const & b) -> int
{
    int n = min(a.n,b.n);
    int distance = 0;
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (a[i][j] == 0 || b[i][j] == 0) continue;
        if (a[i][j] != b[i][j]) {
            distance++;
        }
    }
    }
    return distance;
}

auto manhattan(node const & a, node const & b) -> int
{
    int n = min(a.n,b.n);
    int distance = 0;
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (a[i][j] == 0 || b[i][j] == 0) continue;
        auto [p,q] = locate(a,b[i][j]);
        distance += abs(p-i) + abs(q-j);
    }
    }
    return distance;
}

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

