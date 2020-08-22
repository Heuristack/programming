#include <iostream>
#include <iomanip>

using namespace std;

struct RecursionTree
{
    RecursionTree(unsigned breadth_limit, unsigned depth_limit): breadth_limit(breadth_limit), depth_limit(depth_limit) {}

    struct Node
    {
        unsigned sequence_num;
        unsigned branch_num;
        unsigned path_len;

        Node(unsigned s, unsigned b, unsigned d) : sequence_num(s), branch_num(b), path_len(d) {}
    };

    auto Explore() -> void
    {
        Node node (node_sequence_num++,0,0);
        Explore(node);
    }

    auto Explore(Node node) -> void
    {
        if (node.path_len != DepthLimit((node))) {
            Visit(node);
            for (auto branch_num = 0; branch_num != BreadthLimit(node); branch_num++) {
                Explore(Node(node_sequence_num++,branch_num,node.path_len+1));
            }
        }
    }

    auto Visit(Node const & n) -> void
    {
        cout << "(" << n.path_len << "," << n.branch_num << "): " << setw(2) << setfill('0') << n.sequence_num << endl;
    }

    auto BreadthLimit(Node const & n) -> unsigned const
    {
        return breadth_limit;
    }

    auto DepthLimit(Node const & n) -> unsigned const
    {
        return depth_limit;
    }

    unsigned node_sequence_num = 0;
    unsigned breadth_limit;
    unsigned depth_limit;
};

int main()
{
    RecursionTree(2,4).Explore();
}

