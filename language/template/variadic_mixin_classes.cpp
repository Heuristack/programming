#include <iostream>
using namespace std;

class Mixin1
{
public:
    Mixin1(int i): m{i} {}
    virtual void func1() { cout << "Mixin1: " << m << endl; }
private:
    int m;
};

class Mixin2
{
public:
    Mixin2(int i): m{i} {}
    virtual void func2() { cout << "Mixin2: " << m << endl; }
private:
    int m;
};

template <typename ... Mixins>
class Type : public Mixins ...
{
public:
    Type(Mixins const & ... mixins): Mixins(mixins) ... {}
    virtual ~Type() {}
};

int main()
{
    Type<Mixin1, Mixin2> a(Mixin1(1), Mixin2(2));
    a.func1();
    a.func2();

    Type<Mixin1> b(Mixin1(3));
    b.func1();
}

