Bucket Exploration
------------------

```C++
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <tuple>

using namespace std;

template<typename unordered_container>
void print_bucket(ostream & s, unordered_container c)
{
    for (auto b = 0; b < c.bucket_count(); b++) {
        s << "[" << b << "]: ";
        for (auto i = c.begin(b); i != c.end(b); i++) {
            s << get<0>(*i) << " ";
        }
        s << "\n";
    }
}

template<typename unordered_container>
void print_bucket_reverse(ostream & s, unordered_container c)
{
    for (auto i = c.begin(); i != c.end(); i++) {
        auto key = get<0>(*i);
        s << "[" << key << "]: " << c.bucket(key) << "\n";
    }
}


int main()
{
    unordered_map<char,string> m = {{'O',"Ocean Park!"}};
    if (auto [i,r] = m.insert({'D',"Disneyland!"}); !r) {
        cout << get<0>(*i) << ": " << get<string>(*i) << endl;
    }
    print_bucket(cout, m);
    print_bucket_reverse(cout, m);
}
```

Tree Search: `BFS` and `DFS`
---------------------------

```C++
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

template <typename vertex, typename graph = map<vertex,set<vertex>>>
graph make_graph(vector<pair<vertex,vertex>> edges)
{
    graph g;
    for (auto e : edges) g[e.first].insert(e.second);
    return g;
}

template <typename vertex, typename graph = map<vertex,set<vertex>>>
void print_graph(graph g)
{
    for (auto i = g.begin(); i != g.end(); i++)
    {
        cout << i->first << ": ";
        for (auto v : i->second) cout << v << " ";
        cout << endl;
    }
}

template <typename vertex, typename graph>
void bfs(graph & g, vertex s)
{
    queue<vertex> frontier;
    frontier.push(s);
    while (!frontier.empty())
    {
        vertex u = frontier.front();
        frontier.pop();
        for (vertex v : g[u])
        {
            frontier.push(v);
        }
        cout << u;
    }
}

template <typename vertex, typename graph>
void dfs(graph & g, vertex u)
{
    cout << u;
    for (vertex v : g[u])
    {
        dfs(g, v);
    }
}

int main()
{
    using vertex = int;
    vector<pair<vertex,vertex>> edges {
        {0,1},{0,2},
        {1,3},{1,4},{2,5},{2,6},
        {3,7},{3,8},{4,9}
    };
    using graph = map<vertex,set<vertex>>;
    graph g = make_graph<vertex>(edges);
    print_graph<vertex>(g);
    bfs(g,0); cout << endl;
    dfs(g,0); cout << endl;
}
```

****

