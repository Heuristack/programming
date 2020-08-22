template <typename State, typename Operator, template<typename> typename Set>
struct StateSpace
{
    void dfs(State v)
    {
        if (v == goal) {
            return;
        }
        for (auto w : expand(v)) {
            dfs(w);
        }
    }

    Set<State> expand(State s)
    {
        Set<State> children;
        return children;
    }

    State initial;
    State goal;
    Set<State> states;
    Set<Operator> operators;
};

int main()
{}

