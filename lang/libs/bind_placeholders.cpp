#include <functional>
#include <iostream>
#include <cstdio>

using namespace std;

auto g(int n1, int n2, int n3, int const & n4, int n5)
{
    string s(100UL,'\0');
    snprintf(s.data(),s.size(),"(%d,%d,%d,%d,%d)",n1,n2,n3,n4,n5);
    printf("%s\n",s.data());
}

int main()
{
    using namespace std::placeholders;
    auto n = 10;
    auto f = bind(g,_2,42,_1,cref(n),n);
    n = n + 2;
    f(1,2,2020);
}

