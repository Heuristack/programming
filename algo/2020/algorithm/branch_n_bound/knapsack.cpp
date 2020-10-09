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
    node(node const & n);
    node & reset();
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

node::node(node const & that)
{
    n = ++k;
    i = that.i + 1;
    items = that.items;
}

node & node::reset()
{
    assert(i > 0);
    items[i-1].reset();
    return *this;
}

ostream & operator << (ostream & s, item const & i)
{
    return s << "(" << i.weight << "," << i.value << ")[" << i.ratio() << "]";
}

ostream & operator << (ostream & s, node const & n)
{
    int weight = 0;
    int value = 0;
    s << "[" << setw(2) << setfill('0') << n.n << ":" << n.i << "]{";
    for (auto const & i : n.items) {
        if (i.has_value()) {
            weight += i->weight;
            value += i->value;
            s << i.value();
        }
    }
    return s << "}=>(" << weight << "," << value << ")";
}

double calculate(node const & n, int weight_upper_bound = 100)
{
    assert(n.i > 0);
    double weight = 0;
    double value = 0;
    for (int i = 0; i < (int)n.items.size(); i++) {
        if (auto const & item = n.items[i]; item.has_value()) {
            if (auto trial_weight = weight + item->weight; trial_weight < weight_upper_bound) {
                weight = trial_weight;
                value += item->value;
            }
            else {
                auto remaining_weight = weight_upper_bound - weight;
                auto weight_ratio = remaining_weight / item->weight;
                value += item->value * weight_ratio;
                break;
            }
        }
    }
    return value;
}

auto explore(node const & n) -> void
{
    cout << endl;
    cout << n << endl;
    if ((n.i - 1) < (int)n.items.size()) {
        node a(n);
        node b(n);
        a.reset();
        cout << a << "=" << calculate(a) << endl;
        cout << b << "=" << calculate(b) << endl;
        if (calculate(a) < calculate(b)) explore(b);
        else explore(a);
    }
}

int main()
{
    node n({{40,40},{50,60},{30,10},{10,10},{10,3},{40,20},{30,60}});
    explore(n);
}

