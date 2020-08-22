template <typename node, typename edge, template<typename> typename set=default_list, template<typename,typename> typename map=default_map>
struct graph : searchable<map<node,set<edge>>>
{
    static_assert(is_same<typename node::vertex_type, typename edge::vertex_type>::value);
    using vertex_type = typename node::vertex_type;
    using this_type = graph<node,edge,set,map>;
    using base_type = map<node,set<edge>>;
    using node_type = node;
    using edge_type = edge;

    template <typename direction>
    static auto make_graph(initializer_list<edge_type> edges) -> this_type
    {
        return graph(edges,direction());
    }
    template <typename direction>
    graph(initializer_list<edge_type> edges, direction d)
    {
        for (auto const & e : edges) insert_edge(e,d);
    }

    template <typename direction>
    static auto make_graph(initializer_list<variant<node_type,edge_type>> varis) -> this_type
    {
        return graph(varis,direction());
    }
    template <typename direction>
    graph(initializer_list<variant<node_type,edge_type>> varis, direction d)
    {
        for (auto const & v : varis) {
            if (holds_alternative<edge_type>(v)) insert_edge(get<edge_type>(v),d);
            if (holds_alternative<node_type>(v)) insert_node(get<node_type>(v));
        }
    }

    template <typename direction>
    static auto make_graph(istream & s) -> this_type
    {
        return graph(s,direction());
    }
    template <typename direction>
    graph(istream & s, direction d)
    {
        for (edge_type e; s >> e;) {
            insert_edge(e,d);
        }
    }

    auto insert_node(vertex_type const & v) -> set<edge_type> & { return base_type::operator[](node_type(v)); }
    auto insert_node(node_type const & n) { insert_node(n.v); }
    auto insert_edge(vertex_type const & v, edge_type const & e) { insert_node(v).insert(e); }
    auto insert_edge(edge_type const & e, enum class   directed) { insert_edge(e.s,e); }
    auto insert_edge(edge_type const & e, enum class undirected) { insert_edge(e.s,e); insert_edge(e.t,edge_type{e}.reverse()); }
};

