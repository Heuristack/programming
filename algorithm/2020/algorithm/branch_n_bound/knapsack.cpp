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

#include "branch_n_bound.hpp"

struct item
{
    double ratio() const
    {
        return 1.0 * value / weight;
    }
    int weight = 0;
    int value = 0;
};

ostream & operator << (ostream & s, item const & i)
{
    return s << "(" << i.weight << "," << i.value << ")[" << i.ratio() << "]";
}

item sigma(vector<optional<item>> items)
{
    int weight = 0;
    int value = 0;
    for (auto const & i : items) {
        if (i.has_value()) {
            weight += i->weight;
            value += i->value;
        }
    }
    return {weight,value};
}

struct node
{
    node(initializer_list<item> const & list, int maximum_allowable_weight);
    node(initializer_list<item> const & list) : node(list,100) {}
    node & include();
    node & exclude();
    auto sigma() const -> int;
    static inline int k = 0;
    int n = 0;
    int i = 0;
    int w = 0;
    vector<optional<item>> items;
};

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

node::node(initializer_list<item> const & list, int maximum_allowable_weight)
{
    for (auto const & item : list) {
        items.emplace_back(item);
    }
    sort(begin(items),end(items),[](auto a, auto b){
        return a->ratio() > b->ratio();
    });
    w = maximum_allowable_weight;
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

auto node::sigma() const -> int
{
    auto [weight,value] = ::sigma(items);
    if (weight <= w) {
        return value;
    }
    return -999;
}

node make_node(node const & n)
{
    node e(n);
    e.n = ++n.k;
    e.i = n.i + 1;
    return e;
}

auto maximum_allowable_weight(node const & n) -> int
{
    return n.w;
}

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

// A branch and bound algorithm for the knapsack problem.
// Kolesar, P.J., 1967.
// Management science, 13(9), pp.723-735.

template <typename item_type> using vector_type = vector<item_type>;
template <typename item_type>
ostream & operator <<(ostream & s, vector_type<item_type> const & subset)
{
    s << "{"; for (auto const & item : subset) s << item; s << "}";
    return s;
}

template <typename item_type>
auto aggregate_subset(vector_type<item_type> subset) -> item_type
{
    item_type subset_total;
    for (auto item : subset) {
        subset_total.weight += item.weight;
        subset_total.value += item.value;
    }
    return subset_total;
}

template <typename item_type, typename subset_type = vector_type<item_type>, typename powerset_type = vector_type<subset_type>>
auto generate(subset_type subset) -> powerset_type
{
    powerset_type powerset;
    if (!subset.empty()) {
        item_type item = subset.back();
        subset.pop_back();
        powerset =  generate<item_type>(subset);
        for (subset_type subset : powerset_type(powerset)) {
            subset.push_back(item);
            powerset.push_back(subset);
        }
    }
    else {
        powerset.push_back(subset);
    }
    return powerset;
}

template <typename item_type>
auto max_value_subset(vector_type<item_type> universe, int maximum_allowable_weight) -> vector_type<item_type>
{
    vector_type<item_type> max_value_subset;
    int max_value = 0;
    for (auto subset : generate<item_type>(universe)) {
        auto aggregate = aggregate_subset(subset);
        if ((aggregate.weight <= maximum_allowable_weight) && (aggregate.value >= max_value)) {
            max_value = aggregate.value;
            max_value_subset = subset;
        }
    }
    return max_value_subset;
}

int main()
{
    initializer_list<item> items = {{40,40},{50,60},{30,10},{10,10},{10,3},{40,20},{30,60}};
    int maximum_allowable_weight = 100;
    node n(items,maximum_allowable_weight);
    cout << branch(n).sigma() << endl;
    cout << explore(n) << endl;
    cout << aggregate_subset(max_value_subset(vector_type<item>(items),maximum_allowable_weight)).value << endl;
}

