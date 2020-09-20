#include <iostream>
#include <cassert>
#include <vector>
#include <set>

template <typename element_t> using normalized_map = std::vector<element_t>;

template <typename element_t, template <typename> typename storage_t = normalized_map>
class union_find
{
public:
    using element_type = element_t;
    using storage_type = storage_t<element_type>;
    using this_type = union_find<element_type, storage_t>;

public:
    union_find(int n) : unions(n)
    {
        leader.resize(n);
        for (int i = 0; i < n; i++) {
            leader[i] = i;
        }
    }

public:
    auto unite(element_type a, element_type b) -> this_type &
    {
        auto ua = find(a);
        auto ub = find(b);
        if (ua != ub) {
            leader[ub] = ua;
            unions--;
        }
        return *this;
    }

    auto find(element_type e) -> element_type
    {
        if (leader[e] != e) return find(leader[e]);
        else return leader[e];
    }

    auto connected(element_type a, element_type b) -> bool
    {
        return (find(a) == find(b));
    }

    auto count() -> size_t
    {
        std::set<element_type> s;
        for (auto e : leader) {
            s.insert(find(e));
        }
        assert(unions == s.size());
        return unions;
    }

public:
    auto operator()(element_type a, element_type b) -> this_type &
    {
        return unite(a,b);
    }

public:
    storage_type leader;
    int unions;
};

int main()
{
    union_find<int> u(10);
    u(4,3)(3,8)(6,5)(9,4)(2,1)(8,9)(5,0)(7,2)(6,1)(1,0)(6,7);
    std::cout << u.count() << std::endl;
}
