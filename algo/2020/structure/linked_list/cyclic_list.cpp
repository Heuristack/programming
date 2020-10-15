#include <iostream>

using namespace std;

#include "linked_list.hpp"
#include "cyclic_list.ipp"

int main()
{
    using node_type = node<char>;
    node_type * a = new node_type('A');
    node_type * b = new node_type('B');
    node_type * c = new node_type('C');
    node_type * d = new node_type('D');
    node_type * e = new node_type('E');
    link(a,b);
    link(b,c);
    link(c,d);
    link(d,e);
    link(e,c);
    auto list = a;
    cout << size(d) << endl;
    cout << *next(a,0) << *next(a,1) << *next(a,2) << *next(a,12) << endl;
    if (auto * x = has_cycle(a); x) cout << (*x) << endl;
}

