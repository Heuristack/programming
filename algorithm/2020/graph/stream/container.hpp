template <typename container, typename iterator = typename container::iterator_type>
auto operator << (ostream & s, container const & c) -> ostream &
{
    for (auto i = begin(c); i != end(c); i++) {
         s << (*i);
    }
    return s;
}

