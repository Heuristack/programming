#include <iostream>
#include <utility>
using namespace std;

template <typename T>
void process_values(T && value)
{
    cout << value << endl;
}

template <typename T1, typename ... Ts>
void process_values(T1 && value1, Ts && ... values)
{
    process_values(forward<T1>(value1));
    process_values(forward<Ts>(values)...);
}

int main()
{
    process_values(1,2,3.14,"...",'!');
}

