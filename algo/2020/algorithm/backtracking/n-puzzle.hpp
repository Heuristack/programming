class node : public board<int>
{
public:
    typedef board<int> base_type;
public:
    node(int n) : base_type(n) {}
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

template <typename distance>
class heuristic
{
public:
    heuristic(distance d, node i, node g, double a, double b)
            : d(d),i(i),g(g),a(a),b(b) {}

public:
    double operator()(node const & e) const
    {
        if (e == g) return 0.0;
        return a * d(e,i) + b * d(e,g);
    }
    operator bool () const { return d != nullptr; }

public:
    distance d = nullptr;
    node i;
    node g;
    double a;
    double b;
};

