#include <initializer_list>
#include <iostream>

using namespace std;

#include "linked_list.hpp"
#include "linked_list.ipp"

int main()
{
    auto list = create_list<int>({3,1,4,1,5,9});
    traverse(list,[](auto const & data){ cout << data; });
    cout << endl;

    remove_if(list,[](auto const & data){ return data == 1; });
    traverse(list,[](auto const & data){ cout << data; });
    cout << endl;

    delete_list(list);
    traverse(list,[](auto const & data){ cout << data; });
    cout << endl;
}

