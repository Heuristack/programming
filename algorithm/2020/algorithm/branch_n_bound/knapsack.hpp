struct item
{
    double ratio() const
    {
        return 1.0 * value / weight;
    }
    int weight = 0;
    int value = 0;
};

item sigma(vector<optional<item>> items)
{
    int weight = 0;
    int value = 0;
    for (auto const & i : items) {
        if (i.has_value()) {
            weight += i->weight;
            value += i->value;
        }
    }
    return {weight,value};
}

ostream & operator << (ostream & s, item const & i)
{
    return s << "(" << i.weight << "," << i.value << ")[" << i.ratio() << "]";
}

struct node
{
    node(initializer_list<item> const & list, int maximum_allowable_weight);
    node(initializer_list<item> const & list) : node(list,100) {}
    node & include();
    node & exclude();
    auto sigma() const -> int;
    static inline int k = 0;
    int n = 0;
    int i = 0;
    int w = 0;
    vector<optional<item>> items;
};

node::node(initializer_list<item> const & list, int maximum_allowable_weight)
{
    for (auto const & item : list) {
        items.emplace_back(item);
    }
    sort(begin(items),end(items),[](auto a, auto b){
        return a->ratio() > b->ratio();
    });
    w = maximum_allowable_weight;
}

node & node::include()
{
    assert(i > 0);
    assert(items[i-1].has_value());
    return *this;
}

node & node::exclude()
{
    assert(i > 0);
    items[i-1].reset();
    return *this;
}

auto node::sigma() const -> int
{
    auto [weight,value] = ::sigma(items);
    if (weight <= w) {
        return value;
    }
    return -999;
}

node make_node(node const & n)
{
    node e(n);
    e.n = ++n.k;
    e.i = n.i + 1;
    return e;
}

auto maximum_allowable_weight(node const & n) -> int
{
   return n.w;
}

ostream & operator << (ostream & s, node const & n)
{
    int weight = 0;
    int value = 0;
    s << "[" << setw(3) << setfill('0') << n.n << ":" << n.i << "]{";
    for (auto const & i : n.items) {
        if (i.has_value()) {
            weight += i->weight;
            value += i->value;
            s << i.value();
        }
    }
    return s << "}=(" << weight << "," << value << ")";
}

