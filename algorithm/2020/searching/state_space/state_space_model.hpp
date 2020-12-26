template <typename state_t, typename operate_t>
class state_space_model
{
public:
    typedef state_t state_type;
    typedef operate_t operate_type;

public:
    state_space_model(state_type i, state_type g) : init(i), goal(g) {}
    state_space_model() = default;

public:
    virtual auto is_goal(state_type s) -> bool { return s == goal; }
    virtual auto visit(state_type) -> void {}
    virtual auto next(state_type s, operate_type o) -> optional<state_type> = 0;

    auto expand(state_type s) -> vector<state_type>
    {
        vector<state_type> next_states;
        for (auto const & o : operates) {
            auto n = next(s,o);
            if (n.has_value()) {
                next_states.push_back(n.value());
            }
        }
        return next_states;
    }

public:
    virtual auto search(state_type s) -> void
    {
        visit(s);
        if (is_goal(s)) return;
        for (auto const & s : expand(s)) {
            search(s);
        }
    }

public:
    set<state_type> states;
    set<operate_type> operates;

public:
    state_type init{};
    state_type goal{};
};

