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
#include <string>
#include <cstdio>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%-10s: %s", object.data(), content.data());
    cout << message << endl;
}

// Receiver
class Receiver1
{
public:
    void action1()
    {
        print_message("Receiver1", "Hello World!");
    }
};

// Command
class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

class Command1 : public Command
{
public:
    void execute() override
    {
        print_message("Command1", "Performing (carrying out) the request ... ");
        receiver1_ptr->action1();
    }

public:
    explicit Command1(Receiver1 * receiver1_ptr): receiver1_ptr{receiver1_ptr} {}
    ~Command1() override { delete receiver1_ptr; }

private:
    Receiver1 * receiver1_ptr = nullptr;
};

// Invoker
class Invoker
{
public:
    void operation()
    {
        print_message("Invoker", "Calling 'execute' on the installed command ... ");
        command_ptr->execute();
    }

public:
    explicit Invoker(Command * command_ptr): command_ptr{command_ptr} {}
    ~Invoker() { delete command_ptr; }

private:
    Command * command_ptr = nullptr;
};

int main()
{
    Invoker invoker {new Command1{new Receiver1{}}};
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

