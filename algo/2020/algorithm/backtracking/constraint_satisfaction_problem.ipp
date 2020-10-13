template <typename type = int>
class permutation : public constraint_satisfaction_problem<type>
{
public:
    typedef constraint_satisfaction_problem<type> base_type;

public:
    permutation(vector<type> const & values, int n)
    : base_type(values), n(n) {}

public:
    auto constraint(vector<type> const & values, size_t k) -> vector<type>;
    auto backtrack(vector<type> values) -> void override;

public:
    auto generate() -> vector<vector<type>>
    {
        backtrack(this->values);
        return permutations;
    }

private:
    vector<vector<type>> permutations;
    int n;
};

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

