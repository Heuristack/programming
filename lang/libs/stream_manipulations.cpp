#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cmath>
#include <ctime>
using namespace std;

int main()
{
    int constexpr i = 42;
    cout << setw(10) << setfill('*') << left << i << endl;
    cout << setw(10) << setfill('*') << right << i << endl;

    int constexpr n = 1 << 31;
    cout << oct << n << endl; cout << setbase( 8) << n << endl;
    cout << hex << n << endl; cout << setbase(16) << n << endl;
    cout << dec << n << endl; cout << setbase(10) << n << endl;

    long double const pi = acos(-1.L);
    cout << setprecision(numeric_limits<decltype(pi)>::digits10+1) << pi << endl;

    string a = to_string(pi);
    cout << quoted(a, '$') << endl;

    time_t t = time(nullptr);
    tm * tm = localtime(&t);
    cout << put_time(tm,"%c %z") << endl;

    cout.imbue(locale("en_US.UTF-8"));
    cout << showbase << put_money(pi) << endl;
    cout << showbase << put_money(pi,true) << endl;
}

