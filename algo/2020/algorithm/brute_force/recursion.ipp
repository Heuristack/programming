auto straight_recursion::explore(node e) -> void
{
    visit(e);
    if (e.d < m) {
        for (int i = 0; i < n; i++) {
            node n(k++,i,e.d+1);
            explore(n);
        }
    }
}

auto generate_recursion::generate(node e) -> vector<node>
{
    vector<node> v;
    if (e.d < m) {
        for (int i = 0; i < n; i++) {
            node n(k++,i,e.d+1);
            v.push_back(n);
        }
    }
    return v;
}

auto generate_recursion::explore(node e) -> void
{
    visit(e);
    for (node const & n : generate(e)) {
        explore(n);
    }
}

