#include <iostream>
#include <string>

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
    using vertex_type = vertex;
    static auto const num_mixins = sizeof...(weight);
    static_assert(num_mixins <= 1);
    static constexpr bool is_weighted() { return num_mixins > 0; }

    explicit node(vertex_type const & v, weight const & ... w) : v(v), weighted<weight>(w) ... {}
    node() : weighted<weight>() ... {}
    vertex_type v{};
};

template <typename node>
struct is_weighted
{
    static bool const value = false;
};

template <typename weight>
struct is_weighted<weighted<weight>>
{
    static bool const value = true;
};

template <typename vertex, typename weight>
struct is_weighted<node<vertex,weight>>
{
    static bool const value = true;
};

template <typename node>
auto trait_test(node const &)
{
    cout << is_weighted<node>::value << endl;
}

int main()
{
    node<string> n("A");
    cout << n.v << endl;

    node<string,double> w("R",3.14);
    cout << w.v << ":" << w.w << endl;

    static_assert(is_same_v<node<string,double>::vertex_type,string>);
    static_assert(is_same_v<node<string,double>::weight_type,double>);

    cout << node<string,double>::num_mixins << endl;

    node<string,double> ok;
    cout << node<string>::is_weighted() << endl;
    cout << node<string,double>::is_weighted() << endl;

    cout << is_weighted<node<string>>::value << endl;
    cout << is_weighted<node<string,double>>::value << endl;
    cout << is_weighted<weighted<int>>::value << endl;

    trait_test(n);
    trait_test(w);

}

