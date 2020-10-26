auto get_track(map<node,node> & parents, node u) -> vector<node>
{
    vector<node> v{u};
    while (parents.find(u) != parents.end()) {
        u = parents[u];
        v.push_back(u);
    }
    return v;
}

template <typename distance>
auto puzzle<distance>::search(node const & e) -> bool
{
    auto compare = [this](node const & a, node const & b) -> bool
    {
        return h(a) > h(b);
    };
    priority_queue<node,vector<node>,decltype(compare)> open(compare);
    open.push(e);
    map<node,node> parents;
    while (!open.empty()) {
        auto u = open.top();
        open.pop();
        close.push_back(u);
        // note : seems not correct, does close[0...n] form a path?
        if (is_goal(u)) {
            auto track = get_track(parents,u);
            cout << close.size();
            cout << ":";
            cout << track.size();
            return 1;
        }
        for (auto const & v : generate(u,h)) {
            if (find(begin(close),end(close),v) != end(close)) {
                continue;
            }
            open.push(v);
            parents[v] = u;
        }
    }
    return 0;
}

