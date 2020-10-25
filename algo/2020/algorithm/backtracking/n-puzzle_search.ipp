template <typename distance>
auto puzzle<distance>::search(node const & e) -> bool
{
    auto compare = [this](node const & a, node const & b) -> bool
    {
        return h(a) > h(b);
    };
    priority_queue<node,vector<node>,decltype(compare)> open(compare);
    open.push(e);
    while (!open.empty()) {
        auto u = open.top();
        open.pop();
        close.push_back(u);
        // note : seems not correct, does close[0...n] form a path?
        if (is_goal(u)) {
            cout << close.size();
            return 1;
        }
        for (auto const & v : generate(u,h)) {
            if (find(begin(close),end(close),v) != end(close)) {
                continue;
            }
            open.push(v);
        }
    }
    return 0;
}

