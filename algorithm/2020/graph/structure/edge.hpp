template <typename weight>
struct weighted
{
    using weight_type = weight;
    using this_type = weighted<weight_type>;

    explicit weighted(weight_type const & w) : w(w) {}
    weighted() = default;

    struct weight_less { bool operator()(this_type const & a, this_type const & b) const { return a.w < b.w; } };

    weight_type w{};
};

struct classified
{
    enum edge_class { unknown, tree, back, cross, forward };
    explicit classified(edge_class c) : c(c) {}
    classified() = default;
    edge_class c = unknown;
};

template <typename vertex, typename ... weight>
struct edge : classified, weighted<weight> ...
{
    static_assert(sizeof...(weight) <= 1);
    using this_type = edge<vertex, weight...>;
    using vertex_type = vertex;

    edge(vertex_type const & s, vertex_type const & t, weight const & ... w) : s(s), t(t), weighted<weight>(w) ... {}
    edge() : weighted<weight>() ... {}
    auto reverse() -> this_type & { swap(s,t); return *this; }

    bool operator < (this_type const & that) const { return tie(s,t) < tie(that.s,that.t); }

    vertex_type s{};
    vertex_type t{};
};

template <typename> struct is_weighted {};
template <typename vertex> struct is_weighted<edge<vertex>> { static bool constexpr value = false; };
template <typename vertex, typename ... weight> struct is_weighted<edge<vertex,weight...>> { static bool constexpr value = true; };

template <typename> struct weight_type {};
template <typename vertex> struct weight_type<edge<vertex>> { using type = int; };
template <typename vertex, typename ... weight> struct weight_type<edge<vertex,weight...>> { using type = typename edge<vertex,weight...>::weight_type; };

