#include <iostream>
#include <string>
using namespace std;

template <typename T>
void process_values(T value)
{
    cout << value << endl;
}

template <typename T1, typename ... Ts>
void process_values(T1 value1, Ts ... values)
{
    process_values(value1);
    process_values(values...);
}

int main()
{
    process_values(1,2,3.14,"...",'!');
}

