#include <initializer_list>
#include <iostream>

using namespace std;

#include "linked_list.hpp"
#include "linked_list.ipp"

int main()
{
    auto list = create_list<int>({3,1,4,1,5,9});
    cout << list << endl;

    remove_if(list,[](auto const & n){
        return n->data == 1;
    });
    cout << list << endl;

    delete_after(list);
    cout << list << endl;

    insert_after(list,new node<int>(7));
    cout << list << endl;

    delete_list(list);
    cout << list << endl;
}

