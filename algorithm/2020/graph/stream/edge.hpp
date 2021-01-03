template <typename vertex, typename ... weight>
auto operator << (ostream & s, edge<vertex,weight...> const & e) -> ostream &
{
    string w; if constexpr (sizeof...(weight)) { w = ":" + to_string(e.w); }
    return s << "(" << e.s << "," << e.t << ":" << e.c << w << ")";
}

template <typename vertex, typename ... weight>
auto operator >> (istream & s, edge<vertex,weight...> & e) -> istream &
{
    s >> e.s >> e.t;
    if constexpr (sizeof...(weight)) { s >> e.w; }
    return s;
}

