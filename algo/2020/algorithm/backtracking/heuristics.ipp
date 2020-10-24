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

