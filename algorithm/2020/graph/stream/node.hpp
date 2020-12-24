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

