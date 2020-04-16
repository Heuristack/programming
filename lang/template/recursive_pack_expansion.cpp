// note : able3<able2<able1<base>>>
template <typename base, template <typename> typename ... ables> struct mixins : ables<base> ... {};
int main()
{}

