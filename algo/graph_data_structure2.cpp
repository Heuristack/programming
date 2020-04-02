#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

template <typename weight>
struct weighted
{
    using weight_type = weight;

    explicit weighted(weight_type const & w) : w(w) {}
    weighted() = default;

    weight_type w{};
};

template <typename vertex, typename ... weight>
struct node : weighted<weight> ...
{
    static_assert(sizeof...(weight) <= 1);
    using this_type = node<vertex, weight...>;
    using vertex_type = vertex;

    explicit node(vertex_type const & v, weight const & ... w) : v(v), weighted<weight>(w) ... {}
    node() : weighted<weight>() ... {}

    bool operator < (this_type const & that) const { return v < that.v; }

    vertex_type v{};
};

template <typename vertex, typename ... weight>
struct edge : weighted<weight> ...
{
    static_assert(sizeof...(weight) <= 1);
    using this_type = node<vertex, weight...>;
    using vertex_type = vertex;

    explicit edge(vertex_type const & s, vertex_type const & t, weight const & ... w) : s(s), t(t), weighted<weight>(w) ... {}
    edge() : weighted<weight>() ... {}

    bool operator < (this_type const & that) const { return tie(s,t) < tie(that.s,that.t); }

    vertex_type s{};
    vertex_type t{};
};

template <typename node, typename edge, template<typename> typename set, template<typename,typename> typename map>
struct graph : map<node,set<edge>>
{
    static_assert(is_same<typename node::vertex_type, typename edge::vertex_type>::value);
    using vertex_type = typename node::vertex_type;

    template <typename direction> graph() : graph(direction()) {}
    graph(enum class directed) {}
    graph(enum class undirect) {}
};

int main()
{
    node<string,double> n;
    edge<string,double> e;
}

