#include <iostream>

using namespace std;

template <typename vertex, typename weight = void>
struct node
{
    using vertex_type = vertex;
    using weight_type = weight;
    node(vertex_type v, weight_type w) : v(v), w(w) {}
    node() = default;
    static std::string name() { return "primary template"; }
    vertex_type v{};
    weight_type w{};
};

template <typename vertex>
struct node<vertex,void>
{
    using vertex_type = vertex;
    node(vertex_type v) : v(v) {}
    node() = default;
    static std::string name() { return "partial specialization"; }
    vertex_type v{};
};

int main()
{
    node<int> n;
    cout << n.name() << endl;
}

