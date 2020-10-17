#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class recursion
{
public:
    struct node
    {
        node(int i, int b, int d) : i(i), b(b), d(d) {}
        node(int i) : node(i,0,0) {}
        node(): node(0,0,0) {}
        int i; int b; int d;
    };

    auto visit(node const & n)
    {
        cout << "(" << n.d << "," << n.b << "): " << setw(2) << setfill('0') << n.i << endl;
    }

public:
    auto explore() -> void { explore(node(k++)); }
    virtual auto explore(node e) -> void = 0;

public:
    recursion(int n, int m) : n(n), m(m) {}
    int k = 0; int n; int m;
};

class implicit_node_generation : public recursion
{
public:
    using recursion::recursion;

public:
    auto explore(node e) -> void override;
};

class explicit_node_generation : public recursion
{
public:
    using recursion::recursion;

public:
    auto generate(node e) -> vector<node>;
public:
    auto explore(node e) -> void override;
};

#include "exploration_recursion.ipp"

int main()
{
    implicit_node_generation(2,2).recursion::explore();
    explicit_node_generation(2,2).recursion::explore();
}

