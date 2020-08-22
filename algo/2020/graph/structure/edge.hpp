template <typename weight>
struct weighted
{
    using weight_type = weight;

    explicit weighted(weight_type const & w) : w(w) {}
    weighted() = default;

    weight_type w{};
};

template <typename vertex, typename ... weight>
struct edge : weighted<weight> ...
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

