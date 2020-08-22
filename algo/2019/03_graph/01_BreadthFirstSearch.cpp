#include "GraphHelper.h"

template <typename Vertex, typename Graph>
auto bfs(Graph & g, Vertex s) -> void
{
    if (g.find(s) == g.end()) return;
    else cout << "bfs: ";

    enum class Status {Discovered,Expanding,Processed};
    struct Node {
        Vertex vertex;
        Vertex parent;
        Weight length = 0;
        Status status = Status::Discovered;
    };

    map<Vertex, Node> closed;
    closed[s] = {s,s};

    queue<Vertex> open;
    open.push(s);
    while (!open.empty()) {
        auto u = open.front();
        open.pop();
        closed[u].status = Status::Expanding;
        for (auto const & v : g[u]) {
            if (closed.find(v) == closed.end()) {
                closed[v] = {v,u,closed[u].length+1,Status::Discovered};
                open.push(v);
            }
        }
        closed[u].status = Status::Processed;
        cout << "[" << u << "<-" << closed[u].parent << ":" << closed[u].length << "]";
    }
}

#ifndef NENTRY
int main()
{
    auto const & E = TADM2::Figure_5_9;
    using Graph = UndirectedUnweightedGraph;
    auto G = make_graph<Graph>(E);
    bfs<Vertex,Graph>(G,"1");
    cout << endl;
}
#endif

