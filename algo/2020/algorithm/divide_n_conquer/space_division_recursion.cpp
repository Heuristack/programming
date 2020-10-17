#include <iostream>
#include <iomanip>
using namespace std;

auto divide(int p, int r) -> void
{
    static int k = 0;
    int d = r - p;
    int m = p + d/2;
    cout << setw(2) << setfill('0') << k++ << ":";
    cout << "(" << p << "," << r << ")";
    cout << "(" << m << "-" << d << ")";
    cout << endl;
    if (d <= 0) return;
    divide(p,m);
    divide(m+1,r);
}

int main()
{
    divide(1,9);
}

