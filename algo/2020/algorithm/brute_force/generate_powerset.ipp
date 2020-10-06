auto recursion::generate_powerset(vector<int> s) -> vector<vector<int>>
{
    if (s.empty()) return {{}};
    auto p = generate_powerset(vector<int>(next(begin(s)),end(s)));
    for (auto a : decltype(p)(p)) {
        a.push_back(*begin(s));
        p.push_back(a);
    }
    return p;
}

auto iteration::generate_powerset(vector<int> s) -> vector<vector<int>>
{
    vector<vector<int>> p;
    for (auto e : s) {
        if (!p.empty()) {
            for (auto q : decltype(p)(p)) {
                q.push_back(e);
                p.push_back(q);
            }
        }
        else {
            p.push_back({});
            p.push_back({e});
        }
    }
    return p;
}

auto optimized::generate_powerset(vector<int> s) -> vector<vector<int>>
{
    vector<vector<int>> p;
    auto const n = 1 << s.size();
    for (auto i = 0; i < n; i++) {
        auto b = bitset<sizeof(decltype(i))>(i);
        vector<int> q;
        for (auto k = 0; k < b.size(); k++) {
            if (b[k]) q.push_back(s[k]);
        }
        p.push_back(q);
    }
    return p;
}

