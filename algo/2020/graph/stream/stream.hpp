template <typename vertex>
auto operator << (ostream & s, node<vertex> const & n) -> ostream &
{
    return s << "(" << n.v << ")";
}

template <typename vertex>
auto operator >> (istream & s, node<vertex> & n) -> istream &
{
    return s >> n.v;
}

template <typename vertex, typename ... weight>
auto operator << (ostream & s, edge<vertex,weight...> const & e) -> ostream &
{
    string w; if constexpr (sizeof...(weight)) { w = ":" + to_string(e.w); }
    return s << "(" << e.s << "," << e.t << w << ")";
}

template <typename vertex, typename ... weight>
auto operator >> (istream & s, edge<vertex,weight...> & e) -> istream &
{
    s >> e.s >> e.t;
    if constexpr (sizeof...(weight)) { s >> e.w; }
    return s;
}

template <typename node, typename edge, template<typename> typename set, template<typename,typename> typename map>
auto operator << (ostream & s, graph<node,edge,set,map> const & g) -> ostream &
{
    for (auto const & [n,v] : g) {
        s << n << ":";
        for (auto const & e : v) {
            s << e;
        }
        s << "\n";
    }
    return s;
}

