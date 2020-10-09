#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>

using namespace std;

template <typename item_type> using vector_type = vector<item_type>;
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

static int const max_weight = 100;
struct item { int weight = 0; int value = 0; };
ostream & operator<<(ostream & s, item const & i) { return s << "(" << i.weight << "," << i.value << ")"; }
vector_type<item> items = { {40,40}, {50,60}, {30,10}, {10,10}, {10,3}, {40,20}, {30,60} };
ostream & operator<<(ostream & s, vector_type<item> const & subset) { s << "{"; for (auto const & item : subset) s << item; s << "}"; return s; }

auto aggregate_subset(vector_type<item> subset) -> item
{
    item subset_total;
    for (auto item : subset) {
        subset_total.weight += item.weight;
        subset_total.value += item.value;
    }
    return subset_total;
}

auto run()
{
    vector_type<item> max_value_subset;
    int max_value = 0;
    for (auto subset : generate<item>(items)) {
        auto aggregate = aggregate_subset(subset);
        if ((aggregate.weight <= max_weight) && (aggregate.value >= max_value)) {
            max_value = aggregate.value;
            max_value_subset = subset;
        }
    }
    cout << max_value_subset << "=" << aggregate_subset(max_value_subset) << endl;
}

int main()
{
    run();
}

