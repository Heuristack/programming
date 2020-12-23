template <typename node_t>
auto traverse(node_t * n) -> map<int,vector<node_t*>>
{
    static map<int,vector<node_t*>> node_map;
    static int depth = 0;
    if (n) {
        node_map[depth++].push_back(n);
        traverse(n->ltree);
        traverse(n->rtree);
        depth--;
    }
    return node_map;
}

template <typename node_t>
auto traverse_iterative(node_t * n) -> map<int,vector<node_t*>>
{
    map<int,vector<node_t*>> node_map;
    int depth = 0;

    queue<node_t*> q;
    if (n) q.push(n);
    int num = q.size();

    while (!q.empty()) {
        n = q.front();
        node_map[depth].push_back(n);
        q.pop();
        num--;
        if (n->ltree) q.push(n->ltree);
        if (n->rtree) q.push(n->rtree);
        if (!num) {
            num = q.size();
            depth++;
        }
    }

    return node_map;
}

struct order
{
    enum class pre;
    enum class btw;
    enum class pos;
};

template <typename order_t, typename node_t>
auto search(node_t * n) -> vector<node_t*>
{
    static vector<node_t*> node_seq;
    if (n) {
        if (is_same<order_t,order::pre>::value) node_seq.push_back(n);
        search<order_t>(n->ltree);
        if (is_same<order_t,order::btw>::value) node_seq.push_back(n);
        search<order_t>(n->rtree);
        if (is_same<order_t,order::pos>::value) node_seq.push_back(n);
    }
    return node_seq;
}

