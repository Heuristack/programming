#include <iostream>
#include <string>
#include <map>
#include <utility>

using namespace std;

int main()
{
    map<int,string> m {{4,"Banada"},{5,"Orange"}};

    if (auto [i,r] = m.insert({2,"Apple"}); r) {
        cout << get<string>(*i) << ": "
             << get<0>(*i) << endl;
    }

    auto node = m.extract(4);
    node.key() = 9;
    if (auto const & insert_return = m.insert(move(node)); insert_return.inserted) {
        cout << get<string>(*insert_return.position) << ": "
             << get<0>(*insert_return.position) << endl;
    }

    for (auto const & [n,s] : m) {
        cout << s << ": " << n << endl;
    }
}

