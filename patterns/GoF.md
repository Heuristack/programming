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
#include <cstdio>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Singleton
{
public:

    static Singleton * get_instance()
    {
        static Singleton * instance_ptr = nullptr;
        if (instance_ptr == nullptr) {
            instance_ptr = new Singleton();
        }
        return instance_ptr;
    }

private:
    Singleton() {}
};

int main()
{
    Singleton * instance_ptr1 = Singleton::get_instance();
    Singleton * instance_ptr2 = Singleton::get_instance();
    if (instance_ptr1 == instance_ptr2) {
        print_message("Singleton", "instantiated only once");
    }
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
```C++
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Handler
{
public:
    Handler() {}
    Handler(Handler * successor): successor{successor} {}

public:
    virtual auto handle_request() -> void
    {
        if (successor != nullptr) {
            successor->handle_request();
        }
    }

    virtual auto can_handle() -> bool
    {
        return 0;
    }

private:
    Handler * successor = nullptr;
};

class Receiver1 : public Handler
{
public:
    Receiver1(): Handler{} {}
    Receiver1(Handler * successor): Handler{successor} {}

public:
    auto handle_request() -> void override
    {
        if (can_handle()) {
            print_message("Receiver1", "Handling the request ... ");
        }
        else {
            print_message("Receiver1", "Passing the request along the chain ... ");
            Handler::handle_request();
        }
    }

    auto can_handle() -> bool override
    {
        return 0;
    }
};

class Receiver2 : public Handler
{
public:
    Receiver2(): Handler{} {}
    Receiver2(Handler * successor): Handler{successor} {}

public:
    auto handle_request() -> void override
    {
        if (can_handle()) {
            print_message("Receiver2", "Handling the request ... ");
        }
        else {
            print_message("Receiver2", "Passing the request along the chain ... ");
            Handler::handle_request();
        }
    }

    auto can_handle() -> bool override
    {
        return 0;
    }
};

class Receiver3 : public Handler
{
public:
    Receiver3(): Handler{} {}
    Receiver3(Handler * successor): Handler{successor} {}

public:
    auto handle_request() -> void override
    {
        if (can_handle()) {
            print_message("Receiver3", "Handling the request ... ");
        }
        else {
            print_message("Receiver3", "Passing the request along the chain ... ");
            Handler::handle_request();
        }
    }

    auto can_handle() -> bool override
    {
        return 1;
    }
};

class Sender
{
public:
    static void main()
    {
        Handler * handler = new Handler{new Receiver1{new Receiver2{new Receiver3{}}}};
        print_message("Sender", "Issuing a request to a handler object ... ");
        handler->handle_request();
        delete handler;
    }
};

int main()
{
    Sender::main();
}

```
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
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Receiver1
{
public:
    void action1()
    {
        print_message("Receiver1", "Hello World!");
    }
};

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
```C++
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Context
{};

class AbstractExpression
{
public:
    AbstractExpression(string const & name): name{name} {}
    virtual ~AbstractExpression() = default;

public:
    virtual void interpret(Context const & context) = 0;
    virtual void add(AbstractExpression * expression) {}
    string const & get_name() const { return name; }

private:
    string name;
};

class NonTerminalExpression : public AbstractExpression
{
public:
   ~NonTerminalExpression() { for (auto expression : expressions)  delete expression;  }
    NonTerminalExpression(string const & name): AbstractExpression{name} {}

public:
    void interpret(Context const & context) override
    {
        print_message(get_name(), "");
        for (auto expression : expressions) {
            print_message("", "interpreting ... " + expression->get_name());
            expression->interpret(context);
        }
        print_message(get_name(), "finished");
    }

    void add(AbstractExpression * expression) override
    {
        expressions.push_back(expression);
    }

private:
    vector<AbstractExpression *> expressions;
};

class TerminalExpression : public AbstractExpression
{
public:
    TerminalExpression(string const & name): AbstractExpression{name} {}
public:
    void interpret(Context const & context) override
    {}
};

class Client
{
public:
    static void main()
    {
        AbstractExpression * nt_expr2 = new NonTerminalExpression("ntExpr2");
        nt_expr2->add(new TerminalExpression(" tExpr3"));
        nt_expr2->add(new TerminalExpression(" tExpr4"));
        nt_expr2->add(new TerminalExpression(" tExpr5"));
        AbstractExpression * nt_expr1 = new NonTerminalExpression("ntExpr1");
        nt_expr1->add(new TerminalExpression(" tExpr1"));
        nt_expr1->add(nt_expr2);
        nt_expr1->add(new TerminalExpression(" tExpr2"));
        Context context;
        nt_expr1->interpret(context);
        delete nt_expr1;
    }
};

int main()
{
    Client::main();
}

```

Iterator
--------
Mediator
--------
```C++
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Mediator;
class Colleague;

class Mediator
{
public:
    virtual void mediate(Colleague * colleague) = 0;
};

class Colleague
{
public:
    Colleague(Mediator * mediator): mediator{mediator} {}
    Mediator * mediator;
};

class Colleague1 : public Colleague
{
public:
    Colleague1(Mediator * mediator): Colleague{mediator} {}
    string const & get_state() const { return state; }
    void set_state(string const & state)
    {
        if (this->state != state) {
            this->state = state;
            print_message("Colleague1", "My state changed to " + state + " Calling my mediator ... ");
            mediator->mediate(this);
        }
    }
    void action1(string state)
    {
        this->state = state;
        print_message("Colleague1", "My state is synchronized to " + state);
    }

private:
    string state;
};

class Colleague2 : public Colleague
{
public:
    Colleague2(Mediator * mediator): Colleague{mediator} {}
    string const & get_state() const { return state; }

    void set_state(string const & state)
    {
        if (this->state != state) {
            this->state = state;
            print_message("Colleague2", "My state changed to " + state + " Calling my mediator ... ");
            mediator->mediate(this);
        }
    }
    void action2(string state)
    {
        this->state = state;
        print_message("Colleague2", "My state is synchronized to " + state);
    }

private:
    string state;
};

class Mediator1 : public Mediator
{
public:
    Colleague1 * colleague1 = nullptr;
    Colleague2 * colleague2 = nullptr;

    void set_colleagues(Colleague1 * colleague1, Colleague2 * colleague2)
    {
        this->colleague1 = colleague1;
        this->colleague2 = colleague2;
    }

    void mediate(Colleague * colleague)
    {
        if (colleague == colleague1) {
            colleague2->action2(colleague1->get_state());
        }
        if (colleague == colleague2) {
            colleague1->action1(colleague2->get_state());
        }
    }
};

int main()
{
    Mediator1 mediator1;
    Colleague1 colleague1(&mediator1);
    Colleague2 colleague2(&mediator1);
    mediator1.set_colleagues(&colleague1, &colleague2);

    print_message("(1)", "Changing state of colleague1");
    colleague1.set_state("(1): Hello,World!");

    print_message("(2)", "Changing state of colleague2");
    colleague2.set_state("(2): Hello,World!");
}

```
Memento
-------
```C++
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Originator
{
public:
    class Memento
    {
    public:
        void set_state(string const & s) { state = s; }
        string const & get_state() const { return state; }
    private:
        string state;
    };

public:
    Memento create_memento() { Memento memento; memento.set_state(state); return memento; }
    void restore(Memento const & memento) { state = memento.get_state(); }

    void set_state(string const & s) { state = s; }
    string const & get_state() const { return state; }

private:
    string state;
};


class Caretaker
{
public:
    static void main()
    {
        Originator originator;
        vector<Originator::Memento> mementos;

        originator.set_state("A");
        mementos.push_back(originator.create_memento());
        print_message("(1)", "Saving current state ...... : " + originator.get_state());

        originator.set_state("B");
        mementos.push_back(originator.create_memento());
        print_message("(2)", "Saving current state ...... : " + originator.get_state());

        originator.restore(mementos[0]);
        print_message("(3)", "Restoring to previous state : " + originator.get_state());
    }
};

int main()
{
    Caretaker::main();
}

```

Observer
--------
State
-----
Strategy
--------
Define a family of algorithms, encapsulate each one, and make them interchangeable.
Strategy lets the algorithm vary independently from clients that use it.
```C++
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Strategy
{
public:
    virtual int algorithm() = 0;
};

class Strategy1 : public Strategy
{
public:
    int algorithm() override
    {
        return 1;
    }
};

class Strategy2 : public Strategy
{
public:
    int algorithm() override
    {
        return 2;
    }
};

class Context
{
public:
    Context(Strategy * s): strategy_ptr{s} {}
    void set_strategy(Strategy * s) { strategy_ptr = s; }

    string operation()
    {
        stringstream s;
        s << "Context: Delegating an algorithm to a strategy: Result = " << strategy_ptr->algorithm();
        return s.str();
    }

private:
    Strategy * strategy_ptr;
};

int main()
{
    Strategy1 s1;
    Strategy2 s2;
    Context context(&s1);
    print_message("(1)", context.operation());
    context.set_strategy(&s2);
    print_message("(2)", context.operation());
}

```

Template Method
---------------
Define the skeleton of an algorithm in an operation, deferring some steps to sub-classes.
Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.

```C++
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class AbstractClass
{
public:
    virtual ~AbstractClass() {}

    void template_method()
    {
        primitive1();
        primitive2();
    }

protected:
    virtual void primitive1() = 0;
    virtual void primitive2() = 0;
};

class SubClass1 : public AbstractClass
{
protected:
    void primitive1() override
    {
        print_message("SubClass1", "Executing primitive1 ... ");
    }

    void primitive2() override
    {
        print_message("SubClass1", "Executing primitive2 ... ");
    }
};

int main()
{
    AbstractClass * object_ptr = new SubClass1();
    object_ptr->template_method();
    delete  object_ptr;
}

```

Visitor
-------
Represent an operation to be performed on the elements of an object structure.
Visitor lets you define a new operation without changing the classes of the elements on which it operates.

```C++
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Visitor;
class ElementA;
class ElementB;

class Element
{
public:
    virtual ~Element() {}
    virtual void accept(Visitor * visitor) = 0;
};

class Visitor
{
public:
    virtual ~Visitor() {}
    virtual void visit(ElementA * e) = 0;
    virtual void visit(ElementB * e) = 0;
};

class ElementA : public Element
{
public:
    void accept(Visitor * visitor) override
    {
        visitor->visit(this);
    }

    string operation()
    {
        return "Hello World from ElementA!";
    }
};

class ElementB : public Element
{
public:
    void accept(Visitor * visitor) override
    {
        visitor->visit(this);
    }

    string operation()
    {
        return "Hello World from ElementB!";
    }
};

class Visitor1 : public Visitor
{
public:
    void visit(ElementA * e) override
    {
        print_message("Visitor1",
                "Visiting (doing something on) ElementA : " + e->operation());
    }
    void visit(ElementB * e) override
    {
        print_message("Visitor1",
                "Visiting (doing something on) ElementB : " + e->operation());
    }
};

class Client
{
public:
    static void main()
    {
        vector<Element *> elements;
        elements.push_back(new ElementA);
        elements.push_back(new ElementB);

        Visitor * visitor = new Visitor1();
        for (auto element : elements) {
            element->accept(visitor);
        }

        for (auto element : elements) {
            delete element;
        }
        delete visitor;
    }
};

int main()
{
    Client::main();
}

```

