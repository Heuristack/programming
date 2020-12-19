#include "GraphHelper.h"

template <typename Vertex, typename Graph>
auto DFS(Graph & g, Vertex u) -> void
{
    if (g.find(u) == g.end()) return;

    enum class Status {Discovered,Expanding,Processed};
    struct Node {
        Vertex vertex;
        Vertex parent;
        Weight length = 0;
        Status status = Status::Discovered;
        unsigned enter = 0;
        unsigned leave = 0;
    };
    static map<Vertex, Node> closed;
    static unsigned time = 0;

    if (closed.find(u) == closed.end()) {
        closed[u] = {u,u};
        cout << "DFS: ";
    }

    cout << "(";
    closed[u].status = Status::Expanding;
    closed[u].enter = time++;
    for (auto const & v : g[u]) {
        if (closed.find(v) == closed.end()) {
            closed[v] = {v,u,closed[u].length+1,Status::Discovered};
            DFS(g,v);
        }
    }
    closed[u].leave = time++;
    closed[u].status = Status::Processed;
    cout << "[" << u << "<-" << closed[u].parent << ":" << closed[u].length << "]";
    cout << ")";
}

#ifndef NENTRY
int main()
{
    auto const & E = TADM2::Figure_5_9;
    using Graph = UndirectedUnweightedGraph;
    auto G = make_graph<Graph>(E);
    DFS<Vertex,Graph>(G,"1");
    cout << endl;
}
#endif

