#include "structure/linked_list/linked_list.h"

int main()
{
    auto list = create_list<int>({3,1,4,1,5,9});
    traverse(list,[](auto n){ cout << n; });
    cout << endl;
}

