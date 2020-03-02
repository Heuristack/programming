#include <iostream>
#include <string>
#include <list>

using namespace std;

int main()
{
    auto iterate = [](auto b, auto e) -> string {
        string out;
        for (auto i = b; i != e; i = next(i)) {
            out.append(to_string(*i));
            if (next(i) != e) out.append(",");
        }
        return out;
    };

    list<int> this_list{3,1,4,1};
    list<int> that_list{5,9,2,6};

    this_list.sort();
    that_list.sort();
    cout << "this list: " << iterate(begin(this_list), end(this_list)) << endl;
    cout << "that list: " << iterate(begin(that_list), end(that_list)) << endl;

    that_list.merge(this_list);
    cout << "this list: " << iterate(begin(this_list), end(this_list)) << endl;
    cout << "that list: " << iterate(begin(that_list), end(that_list)) << endl;

    this_list.splice(begin(this_list), that_list);
    cout << "this list: " << iterate(begin(this_list), end(this_list)) << endl;
    cout << "that list: " << iterate(begin(that_list), end(that_list)) << endl;

    that_list.splice(begin(that_list), this_list, next(begin(this_list),2), prev(end(this_list),2));
    cout << "this list: " << iterate(begin(this_list), end(this_list)) << endl;
    cout << "that list: " << iterate(begin(that_list), end(that_list)) << endl;
}

