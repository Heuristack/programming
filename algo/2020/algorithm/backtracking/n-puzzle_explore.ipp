template <typename distance>
auto puzzle<distance>::explore(node const & e) -> bool
{
    close.push_back(e);
    path.push_back(e);
    if (is_goal(e)) {
        cout << path.size();
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

