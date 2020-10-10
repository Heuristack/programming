#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>

using namespace std;

static int constexpr allowable_weight = 100;

typedef struct { int weight = 0; int value = 0; } item_type;
ostream & operator<<(ostream & s, item_type const & i) { return s << "(" << i.weight << "," << i.value << ")"; }

template <typename item_type> using vector_type = vector<item_type>;
ostream & operator<<(ostream & s, vector_type<item_type> const & subset) { s << "{"; for (auto const & item : subset) s << item; s << "}"; return s; }

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

auto max_value_subset(vector_type<item_type> universalset) -> vector_type<item_type>
{
    vector_type<item_type> max_value_subset;
    int max_value = 0;
    for (auto subset : generate<item_type>(universalset)) {
        auto aggregate = aggregate_subset(subset);
        if ((aggregate.weight <= allowable_weight) && (aggregate.value >= max_value)) {
            max_value = aggregate.value;
            max_value_subset = subset;
        }
    }
    return max_value_subset;
}

int main()
{
    vector_type<item_type> const items = {{40,40},{50,60},{30,10},{10,10},{10,3},{40,20},{30,60}};
    cout << aggregate_subset(max_value_subset(items)).value << endl;
}

