#include <iostream>
#include <iomanip>
using namespace std;

auto conquer(int k, int p, int m, int r, int d) -> void
{
    cout << setw(2) << setfill('0') << k++ << ":";
    cout << "(" << p << "," << r << ")";
    cout << "(" << m << "-" << d << ")";
    cout << endl;
}

auto divide(int p, int r) -> void
{
    static int k = 0;
    int d = r - p;
    int m = p + d/2;
    conquer(k,p,m,r,d);
    if (d <= 0) return;
    divide(p,m);
    divide(m+1,r);
}

int main()
{
    divide(1,9);
}

