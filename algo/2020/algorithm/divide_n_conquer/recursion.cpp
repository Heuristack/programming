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
    virtual auto explore() -> void = 0;

public:
    recursion(int n, int m) : n(n), m(m) {}
    int k = 0; int n; int m;
};

class straight_recursion : public recursion
{
public:
    using recursion::recursion;
    auto explore() -> void override { explore(node(k++)); }

public:
    auto explore(node e) -> void;
};

class generate_recursion : public recursion
{
public:
    using recursion::recursion;
    auto explore() -> void override { explore(node(k++)); }

public:
    auto generate(node e) -> vector<node>;
    auto explore(node e) -> void;
};

#include "recursion.ipp"

int main()
{
    straight_recursion(2,2).explore();
    generate_recursion(2,2).explore();
}

