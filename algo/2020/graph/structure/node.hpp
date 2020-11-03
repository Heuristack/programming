template <typename vertex>
struct node
{
    using this_type = node<vertex>;
    using vertex_type = vertex;
    node(vertex_type const & v) : v(v) {}
    node() = default;
    bool operator  < (this_type const & that) const { return v  < that.v; } // TODO: vertex concept requires order relation
    bool operator == (this_type const & that) const { return v == that.v; }
    bool operator != (this_type const & that) const { return v != that.v; }
    vertex_type v{};
};

template <typename node>
struct parent
{
    using node_type = node;
    using vertex_type = typename node_type::vertex_type;
    parent(vertex_type const & p) : p(p) {}
    parent() = default;
    vertex_type p{};
};

template <typename weight>
struct length
{
    using weight_type = weight;
    using this_type = length<weight_type>;
    length(weight_type const & l) : l(l) {}
    length() = default;
    weight_type l{};
    struct length_greater { bool operator () (this_type const & a, this_type const & b) const { return a.l > b.l; } };
    struct length_less    { bool operator () (this_type const & a, this_type const & b) const { return a.l < b.l; } };
};

struct status
{
    enum status_type { discovered, expanding, processed };
    status(status_type s) : s(s) {}
    status() = default;
    status_type s = discovered;
};

template <typename time = unsigned>
struct access
{
    using time_type = time;
    access(time_type t) : enter(t),leave(t) {}
    access() = default;
    time_type enter{};
    time_type leave{};
};

template <typename base, typename ... properties>
struct mixin : base, properties ...
{
    using base_type = base;
    mixin(base_type const & b, properties const & ... p) : base_type(b), properties(p) ... {}
    mixin(base_type const & b) : base_type(b) {}
    mixin() : base_type() {}
};

