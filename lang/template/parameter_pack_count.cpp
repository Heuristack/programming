#include <iostream>
using namespace std;

template <typename ... Ts>
auto count(Ts ...)
{
    return sizeof ... (Ts);
}

template <typename ... Ts>
struct CountTypes
{
    static constexpr int value = sizeof ... (Ts);
};

int main()
{
    cout << count(1,2.3,"3.4",4,'5') << endl;
    cout << CountTypes<int,double,char*,int,char>::value << endl;
}

