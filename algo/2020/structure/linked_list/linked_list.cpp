#include "linked_list.h"

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

