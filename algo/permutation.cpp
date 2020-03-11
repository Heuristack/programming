#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    string s = "abc";
    sort(begin(s),end(s));
    do { cout << s << endl; }
    while (next_permutation(begin(s),end(s)));
}

