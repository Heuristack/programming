#include <iostream>
#include <thread>

using namespace std;

int main()
{
    cout << this_thread::get_id() << endl;
}

