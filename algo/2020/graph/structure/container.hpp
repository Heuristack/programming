template <typename container>
struct sequential : container
{
    using value_type = typename container::value_type;
    using container::container;

    auto get() -> value_type
    {
        value_type v;
        if constexpr (is_same<container,queue<value_type>>::value) { v = this->front(); }
        else { v = this->top(); }
        this->pop();
        return v;
    }
    auto put(value_type const & v)
    {
        this->push(v);
    }
};
template <typename item> using default_stack = sequential<stack<item>>;
template <typename item> using default_queue = sequential<queue<item>>;

template <typename container>
struct insertable : container
{
    using container::container;
    auto insert(typename container::value_type const & v) { return this->push_back(v); }
};
template <typename item> using default_list = insertable<list<item>>;

template <typename container>
struct searchable : container
{
    using container::container;
    auto contains(typename container::key_type const & k) const { return this->find(k) != this->end(); } // note : C++20 feature!
    auto get(typename container::key_type & k) -> typename container::value_type & { return *(this->find(k)); }
};

template <typename container>
struct nonsearchable : container
{
    using container::container;
    auto contains(typename container::value_type const & v) const { return find(begin(*this),end(*this),v) != end(*this); }
    auto get(typename container::value_type const & v) -> typename container::value_type & { return *find(begin(*this),end(*this),v); }
};

template <typename container>
struct extractable : container
{
    using container::container;
    template <typename compare> auto extract_min() -> typename container::value_type
    {
        auto i = min_element(begin(*this),end(*this),compare()); auto v = *i; this->erase(i); return v;
    }
    template <typename compare> auto extract_max() -> typename container::value_type
    {
        auto i = max_element(begin(*this),end(*this),compare()); auto v = *i; this->erase(i); return v;
    }
};

template <typename key> using default_set = searchable<set<key>>;
template <typename key, typename value> using default_map = searchable<map<key,value>>;

