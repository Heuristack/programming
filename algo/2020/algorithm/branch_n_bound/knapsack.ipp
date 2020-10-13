auto explore(node const & n) -> int
{
//  cout << "==" << n << endl;
    static int max_value = 0;
    if (n.i < (int)(n.items.size())) {
        node a = make_node(n).exclude();
        node b = make_node(n).include();
//      cout << "->" << a << "=>B(" << a.n << ")=" << bound(a) << endl;
//      cout << "->" << b << "=>B(" << b.n << ")=" << bound(b) << endl;
        explore(a);
        explore(b);
    }
    else {
        auto value = n.sigma();
        if (value > max_value) {
            max_value = value;
        }
    }
    return max_value;
}

