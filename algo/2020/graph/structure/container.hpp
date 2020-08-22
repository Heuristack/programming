template <typename container>
struct sequential : container
{
    using base_type = container;
    using value_type = typename base_type::value_type;
    auto get() -> value_type
    {
        value_type v;
        if constexpr (is_same<base_type,stack<value_type>>::value) { v = base_type::top();   }
        if constexpr (is_same<base_type,queue<value_type>>::value) { v = base_type::front(); }
        base_type::pop();
        return v;
    }
    auto put(value_type const & v)
    {
        base_type::push(v);
    }
};
template <typename item> using default_stack = sequential<stack<item>>;
template <typename item> using default_queue = sequential<queue<item>>;

template <typename container>
struct insertable : container
{
    auto insert(typename container::value_type const & v) { return container::push_back(v); }
};
template <typename item> using default_list = insertable<list<item>>;

template <typename container>
struct searchable : container
{
    auto contains(typename container::key_type const & k) const { return container::find(k) != container::end(); } // note : C++20 feature!
    auto get(typename container::key_type & k) -> typename container::value_type & { return *container::find(k); }
};
template <typename key> using default_set = searchable<set<key>>;
template <typename key, typename value> using default_map = searchable<map<key,value>>;

