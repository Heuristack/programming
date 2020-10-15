#include <initializer_list>
#include <iostream>

using namespace std;

#include "linked_list.hpp"
#include "linked_list.ipp"

int main()
{
    auto list = create_list<int>({3,1,4,1,5,9});
    auto show = [](auto list){
        cout << "["; traverse(list,[](auto n){ cout << n; }); cout << "]" << endl;
    };
    show(list);

    remove_if(list,[](auto const & n){
        return n->data == 1;
    });
    show(list);

    delete_list(list);
    show(list);
}

