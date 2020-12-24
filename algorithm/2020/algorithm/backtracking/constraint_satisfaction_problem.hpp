template <typename type>
class constraint_satisfaction_problem
{
public:
    constraint_satisfaction_problem(vector<type> const & values)
    : values(values) {}

public:
    template <typename ... types> auto constraint(types ...) -> vector<type>;
    virtual auto backtrack(vector<type> values) -> void = 0;

public:
    vector<type> variables;
    vector<type> values;
};

