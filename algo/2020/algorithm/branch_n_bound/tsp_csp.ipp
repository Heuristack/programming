struct node
{
    node(vector<int> p, vector<int> c): path(p),cans(c) {}
    node() = default;
    vector<int> path;
    vector<int> cans;
};

auto show(vector<int> const & v) -> void
{
    cout << "(";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
    }
    cout << ")";
}

auto show(node const & n) -> void
{
    show(n.path);
    show(n.cans);
    cout << endl;
}

auto cost(vector<int> path, vector<vector<int>> const & cm) -> int
{
    path.push_back(1);
    int path_cost = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        path_cost += cm[path[i]-1][path[i+1]-1];
    }
    return path_cost;
}

auto generate(node const & e) -> vector<node>
{
    vector<node> v;
    for (auto i = begin(e.cans); i != end(e.cans); i++) {
        node n(e);
        n.path.push_back(*i);
        n.cans.erase(next(begin(n.cans),distance(begin(e.cans),i)));
        v.push_back(n);
    }
    return v;
}

auto explore(node const & e) -> vector<int> const &
{
    static vector<int> min_cost_path;
    static int min_cost = mx;

    if (e.cans.empty()) {
        if (auto path_cost = cost(e.path,cm); path_cost < min_cost) {
            min_cost = path_cost;
            min_cost_path = e.path;
        }
    }
    for (auto const & n : generate(node(e))) {
        explore(n);
    }
    return min_cost_path;
}

