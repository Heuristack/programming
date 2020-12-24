#include <type_traits>
#include <iostream>
#include <iomanip>
using namespace std;

template <typename T1, typename T2>
typename enable_if<is_same<T1,T2>::value,bool>::type
check(T1 const & t1, T2 const & t2)
{
    cout << quoted(to_string(t1)) << " and " << quoted(to_string(t2)) << endl;
    return 1;
}

template <typename T1, typename T2>
typename enable_if<!is_same<T1,T2>::value,bool>::type
check(T1 const & t1, T2 const & t2)
{
    cout << quoted(to_string(t1)) << " and " << quoted(to_string(t2)) << endl;
    return 0;
}

int main()
{
    check(2,4);
    check(2,4.2);
}

