class node : public board<int>
{
public:
    typedef board<int> base_type;
public:
    node(int n): base_type(n) {}
};

ostream & operator << (ostream & s, vector<node> const & v)
{
    for (auto const & e : v) {
        s << e;
    }
    return s;
}

auto make(vector<vector<int>> m) -> node
{
    node b(m.size());
    for (int i = 0; i < b.n; i++) {
    for (int j = 0; j < b.n; j++) {
        b[i][j] = m[i][j];
    }
    }
    return b;
}

auto locate(node const & b, int x = 0) -> pair<int,int>
{
    for (int i = 0; i < b.n; i++) {
    for (int j = 0; j < b.n; j++) {
        if (b[i][j] == x) {
            return {i,j};
        }
    }
    }
    return {0,0};
}

static auto goal = make({
    {0,1,2},
    {3,4,5},
    {6,7,8},
});

auto is_goal(node const & e) -> bool
{
    return (e == goal);
}

