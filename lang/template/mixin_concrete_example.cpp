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

    explicit node(vertex_type const & v, weight const & ... w) : v(v), weighted<weight>(w) ... {}
    node() : weighted<weight>() ... {}
    vertex_type v{};
};

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
}

