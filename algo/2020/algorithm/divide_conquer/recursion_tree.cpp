#include <iostream>
#include <iomanip>

using namespace std;

struct recursion_tree
{
    recursion_tree(unsigned breadth_limit, unsigned depth_limit): breadth_limit(breadth_limit), depth_limit(depth_limit) {}

    struct node
    {
        unsigned sequence_num;
        unsigned branch_num;
        unsigned path_len;

        node(unsigned s, unsigned b, unsigned d) : sequence_num(s), branch_num(b), path_len(d) {}
    };

    auto explore() -> void
    {
        node n(node_sequence_num++,0,0);
        explore(n);
    }

    auto explore(node n) -> void
    {
        if (n.path_len != depth_bound((n))) {
            visit(n);
            for (auto branch_num = 0; branch_num != branch_bound(n); branch_num++) {
                explore(node(node_sequence_num++,branch_num,n.path_len+1));
            }
        }
    }

    auto visit(node const & n) -> void
    {
        cout << "(" << n.path_len << "," << n.branch_num << "): " << setw(2) << setfill('0') << n.sequence_num << endl;
    }

    auto branch_bound(node const & n) -> unsigned const
    {
        return breadth_limit;
    }

    auto depth_bound(node const & n) -> unsigned const
    {
        return depth_limit;
    }

    unsigned node_sequence_num = 0;
    unsigned breadth_limit;
    unsigned depth_limit;
};

int main()
{
    recursion_tree(2,4).explore();
}

