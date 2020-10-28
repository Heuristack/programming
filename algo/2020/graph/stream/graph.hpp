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

