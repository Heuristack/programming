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

