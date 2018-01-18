Lambda: Function Procedure Thread Task
======================================

```C++
#include <iostream>
#include <thread>
#include <future>

using namespace std;

int main()
{
    //--------------
    // Pure Function
    //--------------
    {
        cout << [](int i)->int{ return i*i; }(10) << endl;
    }

    //----------------------
    // Side-Effect Procefure
    //----------------------
    {
        int r = 0;
        [&r](int i){ r = i*i; }(10);
        cout << r << endl;
    }

    //-----------------------------
    // Thread Binds a Pure Function
    //-----------------------------
    {
        thread z([](int i)->int{ return i*i; }, 10);
        z.join();
    }

    //------------------------------------
    // Thread Bind a Side-Effect Procedure
    //------------------------------------
    {
        int r = 0;
        thread z{[&r](int i){ r = i*i; }, 10};
        z.join();
        cout << r << endl;
    }

    //--------------
    // Packaged Task
    //--------------
    {
        packaged_task<int(int)> t{[](int i)->int{ return i*i; }};
        t(10);
        cout << t.get_future().get() << endl;
    }
    //------
    // async
    //------
    {
        auto f = async(std::launch::async, [](int i)->int{ return i*i; }, 10);
        cout << f.get() << endl;
    }
    return 0;
}
```

Parameterize Random Number Generation
-------------------------------------

```C++
#include <iostream>
#include <random>

using namespace std;

template <typename device = random_device, typename engine = default_random_engine, typename distribution = normal_distribution<double>>
typename distribution::result_type generate()
{
    static device dev;
    engine eng(dev());
    distribution dis;

    return dis(eng);
}

int main()
{
    for (int i = 0; i < 10; i++) std::cout << generate() << std::endl;
}

```
Priority Queue: Sorting Criterion
---------------------------------

```C++
struct z
{
    int x = 0; int y = 0;
    z(int a): x{a}, y{a-1}{}
    bool operator < (const z that) const { return x < that.x; }
};
ostream & operator << (ostream & s, z o) { s << "(" << o.x << "," << o.y << ")"; return s; }


int main()
{
    priority_queue<z> q;
    q.emplace(3); q.emplace(1); q.emplace(4); q.emplace(1); q.emplace(5);
    while (!q.empty()) { cout << q.top() << endl; q.pop(); }
}
```

```C++
struct z
{
    int x = 0; int y = 0;
    z(int a): x{a}, y{a-1}{}
    struct lessthan { bool operator ()(z a, z b){ return a.x < b.x; } };
};
ostream & operator << (ostream & s, z o) { s << "(" << o.x << "," << o.y << ")"; return s; }

int main()
{
    priority_queue<z, vector<z>, z::lessthan> q;
    q.emplace(3); q.emplace(1); q.emplace(4); q.emplace(1); q.emplace(5);
    while (!q.empty()) { cout << q.top() << endl; q.pop(); }
}
```

Bucket Exploration
------------------

```C++
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <utility>

using namespace std;

template <typename key_type, typename value_type>
ostream & operator << (ostream & s, pair<key_type,value_type> p)
{
    s << "(" << get<0>(p) << ", " << get<1>(p) << ")";
    return s;
}

template<typename unordered_container>
void print_bucket(ostream & s, unordered_container c)
{
    for (auto b = 0; b < c.bucket_count(); b++) {
        s << "[" << b << "]: ";
        for (auto i = c.begin(b); i != c.end(b); i++) {
            s << *i;
        }
        s << "\n";
    }
}

template<typename unordered_container>
void print_bucket_reverse(ostream & s, unordered_container c)
{
    for (auto i = c.begin(); i != c.end(); i++) {
        typename unordered_container::key_type key;
        if constexpr (is_same<typename unordered_container::key_type,
                              typename unordered_container::value_type>::value) {
            key = *i;
        }
        else {
            key = get<0>(*i);
        }
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

    unordered_set<string> s = {"O"};
    if (auto [i,r] = s.insert("D"); !r) {
        cout << *i << endl;
    }
    print_bucket(cout, s);
    print_bucket_reverse(cout, s);
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

