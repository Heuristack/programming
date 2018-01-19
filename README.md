Precision on Stream
===================

```C++
#include <iostream>
#include <iomanip>

int main(int n, char * v[])
try {
    std::cout << std::fixed << std::setprecision(std::stoi(std::string(v[2]))) << std::stod(std::string(v[1])) << std::endl;
}
catch(std::exception & e) {
    std::cout << "exception: " << e.what() << std::endl;
    std::cout << "usage: " << v[0] << " double precision" << std::endl;
}
```

Count Words using Unique-Map
============================

```C++
#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    istream_iterator<string> e, i(cin);
    vector<string> v;
    copy(i, e, back_inserter(v));
    cout << "N = " << v.size() << endl;
    sort(v.begin(), v.end());
    unique(v.begin(), v.end());

    map<string, long> m;
    for (const auto & w : v) {
        auto p = m.find(w);
        if (p != m.end()) {
            p->second++;
        }
        else {
            m.insert(std::make_pair(w,1));
        }
    }

    vector<pair<long, string>> s;
    for (const auto & p : m) { s.push_back(make_pair(p.second, p.first)); }
    sort(s.begin(), s.end(), [](decltype(s)::value_type a, decltype(s)::value_type b){ return a.first > b.first; });
    for (const auto & p : s) { cout << p.first << ": " << p.second << endl; }
}
```

Stream Iterators and Transform Algorithm
========================================
```C++
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    istream_iterator<string> e,i(cin);
    ostream_iterator<string> o(cout);
    vector<string> names;
    copy(i,e,back_inserter(names));
    vector<string> lines;
    transform(names.begin(),names.end(),back_inserter(lines),[](string const & s){ return s + "\n"; });
    copy(lines.begin(),lines.end(),o);
}
```

CCIA File Name Parser
=====================

```C++
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <tuple>
#include <sstream>
#include <cctype>

int main()
{
    std::istream_iterator<std::string> e;
    std::istream_iterator<std::string> i(std::cin);
    std::ostream_iterator<std::string> o(std::cout, " ");

    std::vector<std::string> names;
    std::copy(i, e, std::back_inserter(names));

    auto seperate = [](const std::string & name) -> std::tuple<std::string, std::string, std::string>
    {
        std::string h,m,t;

        auto pu = name.find("_");
        auto pd = name.rfind(".");
        if (pu != std::string::npos && pd != std::string::npos) {
            h = name.substr(0, pu);
            m = name.substr(pu + 1, (pd - pu - 1));
            t = name.substr(pd, name.size());
        }

        return std::make_tuple(h,m,t);
    };

    auto align = [](std::string & s)
    {
        auto c = s[0];
        if (std::isdigit(c)) { s.insert(0, "0"); }
        if (std::isalpha(c)) { s[0] = std::toupper(c); s.insert(0, "A"); }
    };

    for (const auto & n : names) {
        std::stringstream stream(std::get<1>(seperate(n)));
        std::string chapter, section;
        std::getline(stream, chapter, '.');
        std::getline(stream, section, '.');

        if (std::max(chapter.size(), section.size()) >= 3) continue;
        if (chapter.size() == 1) { align(chapter); }
        if (section.size() == 1) { align(section); }

        std::cout << chapter << section << std::endl;
    }
}
```

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

