template <typename node, typename edge, template<typename> typename set=default_list>
class tree
{
public:
    static_assert(is_same<typename node::vertex_type, typename edge::vertex_type>::value);
    using node_type = node;
    using edge_type = edge;
    template<typename type> using set_type = set<type>;

public:
    auto contains(node_type const & n) const -> bool { return true; }

public:
    virtual auto operator[](node_type const & n) -> set_type<edge_type> = 0;
};

// A problem-space graph is often used to represent a problem space.
// Although most problem spaces correspond to graphs with more than one path between a pair of nodes,
// for simplicity they are often represented as trees,
// where the initial state is the root of the tree.
// Korf, R.E., 1999. Artificial intelligence search algorithms.

