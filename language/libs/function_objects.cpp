#include <iostream>
#include <functional>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;

bool is_integer(string_view s)
{
    class is_digit
    {
    public:
        bool operator() (char c) const { return isdigit(c); }
    };

//  return find_if(begin(s),end(s),not_fn(is_digit())) == end(s);
    return all_of(begin(s),end(s),is_digit());
}

int main()
{
    cout << is_integer("1234") << endl;
    cout << is_integer("3.14") << endl;
}

