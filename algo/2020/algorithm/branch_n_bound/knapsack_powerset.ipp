template <typename item_type> using vector_type = vector<item_type>;

template <typename item_type>
ostream & operator <<(ostream & s, vector_type<item_type> const & subset) { s << "{"; for (auto const & item : subset) s << item; s << "}"; return s; }

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
auto max_value_subset(vector_type<item_type> universalset, int maximum_allowable_weight) -> vector_type<item_type>
{
    vector_type<item_type> max_value_subset;
    int max_value = 0;
    for (auto subset : generate<item_type>(universalset)) {
        auto aggregate = aggregate_subset(subset);
        if ((aggregate.weight <= maximum_allowable_weight) && (aggregate.value >= max_value)) {
            max_value = aggregate.value;
            max_value_subset = subset;
        }
    }
    return max_value_subset;
}

