#include <iostream>

using namespace std;

#include "linked_list.hpp"
#include "cyclic_list.ipp"

int main()
{
    using node_t = node<char>;
    auto * a = new node_t('A');
    auto * b = new node_t('B');
    auto * c = new node_t('C');
    auto * d = new node_t('D');
    auto * e = new node_t('E');
    link(a,b);
    link(b,c);
    link(c,d);
    link(d,e);
    link(e,c);
    cout << size(d) << endl;
    cout << next(a,0) << next(a,1) << next(a,2) << next(a,12) << endl;
    if (auto * x = has_cycle(a); x) cout << x << endl;
}

