#include <type_traits>
#include <iostream>
#include <string>
#include <utility>

using std::string;
using std::cout;
using std::endl;
using std::remove_reference;
using std::move;

namespace explicit_return {
template <typename type> type&& forward(typename remove_reference<type>::type&  value) { cout << "ecp:"; return static_cast<type&&>(value); }
template <typename type> type&& forward(typename remove_reference<type>::type&& value) { cout << "emv:"; return static_cast<type&&>(value); }
}

namespace implicit_return {
template <typename type> decltype(auto) forward(typename remove_reference<type>::type&  value) { cout << "icp:"; return static_cast<type&&>(value); } // note : decltype(auto) is necessary
template <typename type> decltype(auto) forward(typename remove_reference<type>::type&& value) { cout << "imv:"; return static_cast<type&&>(value); } //        to preserve reference-ness!
}

void print(string const & value) { cout << "c:" << value << endl; }
void print(string &  value)      { cout << "l:" << value << endl; }
void print(string && value)      { cout << "r:" << value << endl; }

template <typename type> void explicit_print(type && value) { print(explicit_return::forward<type>(value)); }
template <typename type> void implicit_print(type && value) { print(implicit_return::forward<type>(value)); }
template <typename type> void indirect_print(type && value) { print(explicit_return::forward<type>(explicit_return::forward<type>(value))); }

int main()
{
    string a("Perfect!");
    string b("Forward!");
    string c("Hello,PF");

    explicit_print(a);
    explicit_print(move(a));
    explicit_print(move(string("Really?")));

    implicit_print(b);
    implicit_print(move(b));
    implicit_print(move(string("Really?")));

    indirect_print(c);
    indirect_print(move(c));
    indirect_print(move(string("Really?")));
}

