struct node
{
    node(vector<vector<int>> const & m): matrix(m) { bound = reduce(matrix); }
    vector<pair<int,int>> path;
    vector<vector<int>> matrix;
    int bound;
};

auto next(vector<pair<int,int>> const & path, int s) -> int
{
    for (auto [i,j] : path) {
        if (i == s) {
            return j;
        }
    }
    return -1;
}

auto show_path(vector<pair<int,int>> const & p) -> void
{
    int s = 0;
    cout << "(" << s + 1;
    for (int i = next(p,0); i > 0; i = next(p,i)) {
        cout << i + 1;
    }
    cout << ")";
}

auto show(vector<pair<int,int>> const & p) -> void
{
    for (auto [i,j] : p) {
        cout << "(" << i << "," << j << ")";
    }
}

auto show(node const & e) -> void
{
    cout << "["; show(e.path); cout << "]" << endl;
    show(e.matrix);
    cout << e.bound << endl;
}

auto exclude(node const & e, int i, int j) -> node
{
    node x(e);
    exclude(x.matrix,i,j);
    x.bound += reduce(x.matrix);
    return x;
}

auto include(node const & e, int i, int j) -> node
{
    node x(e);
    include(x.matrix,i,j);
    for (auto [m,p] : e.path) {
        if (p == i) {
            exclude(x.matrix,j,m);
        }
        if (j == m) {
            exclude(x.matrix,p,i);
        }
    }
    exclude(x.matrix,j,i);
    x.path.emplace_back(i,j);
    x.bound += reduce(x.matrix);
    return x;
}

auto choose(node const & e) -> pair<int,int>
{
    int i = 0, j = 0;
    if (auto t = theta(e.matrix); !zero(t)) {
        tie(i,j) = max_element(t);
    }
    else {
        tie(i,j) = cans(e.matrix).back();
    }
    return {i,j};
}

auto explore(node const & e) -> node
{
    if (e.path.size() == n) {
        return e;
    }
    auto [i,j] = choose(e);
    auto a = exclude(e,i,j);
    auto b = include(e,i,j);
    if (a.bound < b.bound) return explore(a);
    else return explore(b);
}

