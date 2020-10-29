template <typename container>
struct sequential : container
{
    using value_type = typename container::value_type;
    using container::container;

    auto get() -> value_type
    {
        value_type v;
        if constexpr (is_same<container,queue<value_type>>::value) { v = container::front(); }
        else { v = container::top(); }
        container::pop();
        return v;
    }
    auto put(value_type const & v)
    {
        container::push(v);
    }
};
template <typename item> using default_stack = sequential<stack<item>>;
template <typename item> using default_queue = sequential<queue<item>>;

template <typename container>
struct insertable : container
{
    using container::container;
    auto insert(typename container::value_type const & v) { return container::push_back(v); }
};
template <typename item> using default_list = insertable<list<item>>;

template <typename container>
struct searchable : container
{
    using container::container;
    auto contains(typename container::key_type const & k) const { return container::find(k) != container::end(); } // note : C++20 feature!
    auto get(typename container::key_type & k) -> typename container::value_type & { return *container::find(k); }
};
template <typename key> using default_set = searchable<set<key>>;
template <typename key, typename value> using default_map = searchable<map<key,value>>;

