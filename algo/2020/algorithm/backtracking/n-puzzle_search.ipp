template <typename distance>
auto puzzle<distance>::search(node const & e) -> bool
{
    auto compare = [](node const & a, node const & b) -> bool
    {
        return h(a) < h(b);
    };
    priority_queue<node,vector<node>,compare> open;

    // TODO

    close.push_back(e);
    return 0;
}

