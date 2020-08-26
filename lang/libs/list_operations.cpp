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
            if (next(i) != e) {
                out.append(",");
            }
        }
        return out;
    };

    list<int> this_list{3,1,4,1};
    list<int> that_list{5,9,2,6};

    auto show_list = [iterate,&this_list,&that_list](string const & title = "") -> void
    {
        cout << title << endl;
        cout << "this=[" << iterate(begin(this_list), end(this_list)) << "] ";
        cout << "that=[" << iterate(begin(that_list), end(that_list)) << "] ";
        cout << endl;
    };

    cout << "Illustration of list operations: sort, merge, splice)" << endl;
    show_list("initial status");

    this_list.sort(); that_list.sort();
    show_list("this.sort();that.sort();");

    that_list.merge(this_list);
    show_list("that.merge(this)");

    this_list.splice(begin(this_list), that_list);
    show_list("this.splice(begin(this),that)");

    that_list.splice(begin(that_list), this_list, next(begin(this_list),2), prev(end(this_list),2));
    show_list("that.splice(begin(that),this,next(begin(this),2),prev(end(this),2))");
}

