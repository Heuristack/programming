template <typename type>
auto permutation<type>::constraint(vector<type> const & values, size_t k) -> vector<type>
{
    vector<type> remaining_values;
    for (size_t i = 0; i < values.size(); i++) {
        if (i != k) {
            remaining_values.push_back(values[i]);
        }
    }
    return remaining_values;
}

template <typename type>
auto permutation<type>::backtrack(vector<type> values) -> void
{
    if (this->variables.size() == n) {
        permutations.push_back(this->variables);
    }

    for (size_t i = 0; i < values.size(); i++) {
        this->variables.push_back(values[i]);
        backtrack(constraint(values,i));
        this->variables.pop_back();
    }
}

