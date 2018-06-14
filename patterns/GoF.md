Abstract Factory
----------------
Builder
-------
Factory Method
--------------
Prototype
---------
Singleton
---------
```C++
#include <iostream>
#include <string>
using namespace std;

class Singleton
{
public:
    Singleton(string const & a): m{a}{}

    static Singleton & instance()
    {
        if (m_instance == nullptr) {
            cout << "Constructing on First Use ... " << endl;
            m_instance = make_unique<Singleton>("The Unique Instance!");
        }
        return *m_instance;
    }

public:
    Singleton & set(string const & a)
    {
        m = a;
        return *this;
    }
    string const & get() const
    {
        return m;
    }

private:
    string m;
    static unique_ptr<Singleton> m_instance;
};
unique_ptr<Singleton> Singleton::m_instance = nullptr;

int main()
{
    cout << Singleton::instance().get() << endl;
    cout << Singleton::instance().get() << endl;
    cout << Singleton::instance().set("Hello,World!").get() << endl;
}

```

Adapter
-------
Bridge
------
Composite
---------
Decorator
---------
Facade
------
Flyweight
---------
Proxy
-----

Chain of Responsibility
-----------------------
Command
-------
```C++
#include <iostream>
using namespace std;

class Receiver1
{
public:
    void action1()
    {
        cout << "Receiver1: Hello, World!" << endl;
    }
};

class Command
{
public:
    virtual void execute() = 0;
};

class Command1 : public Command
{
public:
    Command1(Receiver1 & receiver1): receiver1(receiver1) {}

    void execute() override
    {
        cout << "Command1: Performing the request ..." << endl;
        receiver1.action1();
    }

private:
    Receiver1 & receiver1;
};

class Invoker
{
public:
    Invoker(Command & command): command(command) {}

    void operation()
    {
        cout << "Invoker  : Calling execute on the installed command ...  " << endl;
        command.execute();
    }

private:
    Command & command;
};

int main()
{
    Invoker invoker{*(new Command1{*(new Receiver1{})})};
    invoker.operation();
}

```

Interpreter
-----------
Iterator
--------
Mediator
--------
Memento
-------
Observer
--------
State
-----
Strategy
--------
Template Method
---------------
Visitor
-------

