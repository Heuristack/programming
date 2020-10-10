#include <iostream>
#include <iomanip>
#include <optional>
#include <vector>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std;

struct item
{
    double ratio() const
    {
        return 1.0 * value / weight;
    }
    int weight;
    int value;
};

struct node
{
    node(initializer_list<item> const & list);
    node & include();
    node & exclude();
    static inline int k = 0;
    int n = 0;
    int i = 0;
    vector<optional<item>> items;
};

node::node(initializer_list<item> const & list)
{
    for (auto const & item : list) {
        items.emplace_back(item);
    }
    sort(begin(items),end(items),[](auto a, auto b){
        return a->ratio() > b->ratio();
    });
}

node & node::include()
{
    assert(i > 0);
    assert(items[i-1].has_value());
    return *this;
}

node & node::exclude()
{
    assert(i > 0);
    items[i-1].reset();
    return *this;
}

node make_node(enum class exclude, node const & n)
{
    node a(n);
    a.n = ++n.k;
    a.i = n.i + 1;
    a.exclude();
    return a;
}

node make_node(enum class include, node const & n)
{
    node a(n);
    a.n = ++n.k;
    a.i = n.i + 1;
    a.include();
    return a;
}

ostream & operator << (ostream & s, item const & i)
{
    return s << "(" << i.weight << "," << i.value << ")[" << i.ratio() << "]";
}

ostream & operator << (ostream & s, node const & n)
{
    int weight = 0;
    int value = 0;
    s << "[" << setw(3) << setfill('0') << n.n << ":" << n.i << "]{";
    for (auto const & i : n.items) {
        if (i.has_value()) {
            weight += i->weight;
            value += i->value;
            s << i.value();
        }
    }
    return s << "}=(" << weight << "," << value << ")";
}

double bound(node const & n, int allowable_weight = 100)
{
    assert(n.i > 0);
    double weight = 0;
    double value = 0;
    for (int i = 0; i < (int)n.items.size(); i++) {
        if (auto const & item = n.items[i]; item.has_value()) {
            if (auto trial_weight = weight + item->weight; trial_weight <= allowable_weight) {
                weight = trial_weight;
                value += item->value;
            }
            else {
                if (i > n.i - 1) {
                    auto remaining_weight = allowable_weight - weight;
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

auto branch(node const & n) -> node
{
//  cout << "==" << n << endl;
    if (n.i < (int)n.items.size()) {
        node a = make_node(exclude(),n);
        node b = make_node(include(),n);
//      cout << "->" << a << "=>B(" << a.n << ")=" << bound(a) << endl;
//      cout << "->" << b << "=>B(" << b.n << ")=" << bound(b) << endl;
        if (bound(a) <= bound(b)) return branch(b);
        else return branch(a);
    }
    else {
        return n;
    }
}

auto totalize(node const & n) -> pair<int,int>
{
    int weight = 0;
    int value = 0;
    for (auto const & i : n.items) {
        if (i.has_value()) {
            weight += i->weight;
            value += i->value;
        }
    }
    return make_pair(weight,value);
}

auto allowable_value(pair<int,int> weight_value, int allowable_weight = 100) -> int
{
    if (get<0>(weight_value) <= allowable_weight) {
        return get<1>(weight_value);
    }
    return -999;
}

auto explore(node const & n) -> int
{
//  cout << "==" << n << endl;
    static int max_value = 0;
    if (n.i < (int)n.items.size()) {
        node a = make_node(exclude(),n);
        node b = make_node(include(),n);
//      cout << "->" << a << "=>B(" << a.n << ")=" << bound(a) << endl;
//      cout << "->" << b << "=>B(" << b.n << ")=" << bound(b) << endl;
        explore(a);
        explore(b);
    }
    else {
        auto value = allowable_value(totalize(n));
        if (value > max_value) {
            max_value = value;
        }
    }
    return max_value;
}

int main()
{
    node n = {{40,40},{50,60},{30,10},{10,10},{10,3},{40,20},{30,60}};
    cout << bound(branch(n)) << endl;
    cout << explore(n) << endl;
}
// Kolesar, P.J., 1967. A branch and bound algorithm for the knapsack problem. Management science, 13(9), pp.723-735.

