#include <iostream>
#include <utility>
#include <string>
#include <type_traits>

using namespace std;

template <typename type, typename return_type = typename std::remove_reference<type>::type &&>
auto move2(type && object) -> return_type
{
    return static_cast<return_type>(object);
}

template <typename type>
auto move1(type && object)
{
    using return_type = typename std::remove_reference<type>::type &&; // note : C++14 return type deduction is more resilient
//  using return_type = type &&; // note : this is incorrect due to the following assert can't always hold!
    static_assert(is_rvalue_reference<return_type>::value);
    if (is_lvalue_reference<return_type>::value) { cout << "lvalue reference" << endl; }
    if (is_rvalue_reference<return_type>::value) { cout << "rvalue reference" << endl; }
    return static_cast<return_type>(object);
}

template <typename type>
auto forward1(typename remove_reference<type>::type & object)
{
    using return_type = type &&;
    return static_cast<return_type>(object);
}

template <typename type>
auto forward1(typename remove_reference<type>::type && object)
{
    static_assert(!is_lvalue_reference<type>::value);
    using return_type = type &&;
    return static_cast<return_type>(object);
}

auto print(std::string const & a) { cout << "cp:" << a << endl; }
auto print(std::string && a) { cout << "mv:" << a << endl; }

template <typename type>
auto process(type && object)
{
    print(forward1<type>(object));
}

int main()
{
    string a = "let's move!";
    string b(move(a));
    cout << a << ":" << b << endl;

    process(b);
    process(move(b));
}

