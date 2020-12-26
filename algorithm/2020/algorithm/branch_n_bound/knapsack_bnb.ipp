auto branch(node const & n) -> node
{
//  cout << "==" << n << endl;
    if (n.i < (int)(n.items.size())) {
        node a = make_node(n).exclude();
        node b = make_node(n).include();
//      cout << "->" << a << "=>B(" << a.n << ")=" << bound(a) << endl;
//      cout << "->" << b << "=>B(" << b.n << ")=" << bound(b) << endl;
        if (bound(a) <= bound(b)) return branch(b);
        else return branch(a);
    }
    else {
        return n;
    }
}

auto bound(node const & n) -> double
{
    assert(n.i > 0);
    double weight = 0;
    double value = 0;
    for (int i = 0; i < (int)n.items.size(); i++) {
        if (auto const & item = n.items[i]; item.has_value()) {
            if (auto trial_weight = weight + item->weight; trial_weight <= maximum_allowable_weight(n)) {
                weight = trial_weight;
                value += item->value;
            }
            else {
                if (i > n.i - 1) {
                    auto remaining_weight = maximum_allowable_weight(n) - weight;
                    auto weight_ratio = remaining_weight / item->weight;
                    value += item->value * weight_ratio;
                }
                else value = -999;
                break;
            }
        }
    }
    return value;
}

// A branch and bound algorithm for the knapsack problem.
// Kolesar, P.J., 1967.
// Management science, 13(9), pp.723-735.
