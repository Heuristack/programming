template <typename element_t, template <typename> typename storage_t>
class union_find
{
public:
    using element_type = element_t;
    using storage_type = storage_t<element_type>;
    using this_type = union_find<element_type, storage_t>;

public:
    union_find(int n) : leader(n), unions(n)
    {
        for (int i = 0; i < n; i++) {
            leader[element_type(i)] = element_type(i);
        }
    }

public:
    auto union_set(element_type a, element_type b) -> this_type &
    {
        auto ua = find_set(a);
        auto ub = find_set(b);
        if (ua != ub) {
            leader[ub] = ua;
            unions--;
        }
        return *this;
    }

    auto find_set(element_type e) -> element_type
    {
        if (leader[e] != e) return find_set(leader[e]);
        else return leader[e];
    }

    auto connected(element_type a, element_type b) -> bool
    {
        return (find_set(a) == find_set(b));
    }

    auto count() -> size_t
    {
        std::set<element_type> s;
        for (auto e : leader) {
            s.insert(find_set(e));
        }
        assert(unions == s.size());
        return unions;
    }

public:
    auto operator()(element_type a, element_type b) -> this_type &
    {
        return union_set(a,b);
    }

public:
    storage_type leader;
    int unions;
};

