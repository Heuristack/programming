template <typename node, typename edge, template<typename> typename set=default_list>
class graph
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

