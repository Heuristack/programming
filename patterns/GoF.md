Abstract Factory
----------------
Builder
-------
Factory Method
--------------
Define an interface for creating an object, but let subclasses decide which class to instantiate.
Factory Method lets a class defer instantiation to subclasses.

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

class Product
{
public:
    virtual ~Product() {}
    virtual string get_name() = 0;
};

class Creator
{
public:
    virtual ~Creator() { delete product; }
    virtual Product * factory_method() = 0;
    void operation()
    {
        product = factory_method();
        print_message("Creator", product->get_name() + " is created");
    }

private:
    Product * product;
};

class Product1 : public Product
{
public:
    string get_name() override
    {
        return "Product1";
    }
};

class Product2 : public Product
{
public:
    string get_name() override
    {
        return "Product2";
    }
};

class Creator1 : public Creator
{
public:
    Product * factory_method() override
    {
        return new Product1();
    }
};

int main()
{
    Creator * creator = new Creator1();
    creator->operation();
}

```

Prototype
---------
Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.

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

class Product
{
public:
    virtual ~Product() {}
    virtual string get_name() = 0;
};

class Prototype
{
public:
    virtual ~Prototype() {}
    virtual Product * clone() = 0;
};

class Product1 : public Product, public Prototype
{
public:
    Product1(string const & name): name{name} {}
    Product1(Product1 const * p): name{p->name} {}

    string get_name() override
    {
        return name;
    }

    Product * clone() override
    {
        print_message("Prototype", "cloning " + get_name());
        return new Product1(this);
    }

private:
    string name;
};

class Client
{
public:
    Client(Prototype * p): prototype{p} {}
   ~Client() { if (product) delete product; delete prototype; }

    void operation()
    {
        product = prototype->clone();
        print_message("Client:", product->get_name() + " cloned");
    }

private:
    Product * product;
    Prototype * prototype;
};

int main()
{
    Client * client = new Client(new Product1("Product1"));
    client->operation();
    delete client;
}

```

Singleton
---------
Ensure a class only has one instance, and provide a global point of access to it.

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
        static Singleton instance;
        return & instance;
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
Convert the interface of a class into another interface clients expect.
Adapter lets classes work together that couldn't otherwise because of incompatible interfaces.

```C++
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%15s : %s", object.data(), content.data());
    cout << message << endl;
}

class Target
{
public:
    virtual ~Target() {}
    virtual string operation() = 0;
};

class Adaptee
{
public:
    string specific_operation() const
    {
        return "Hello World from Adaptee!";
    }
};

class ObjectAdapter : public Target
{
public:
    ObjectAdapter(Adaptee * a): adaptee{a} {}
   ~ObjectAdapter() { delete adaptee; }
    string operation() override
    {
        return adaptee->specific_operation();
    }

private:
    Adaptee * adaptee;
};

class ClassAdapter : public Target, public Adaptee
{
public:
    string operation() override
    {
        return specific_operation();
    }
};

class Client
{
public:
    static void main()
    {
        Target * object_target = new ObjectAdapter(new Adaptee());
        print_message("ObjectAdapter", object_target->operation());
        Target * class_target = new ClassAdapter();
        print_message("ClassAdapter", class_target->operation());
        delete object_target;
    }
};

int main()
{
    Client::main();
}

```

Bridge
------
Decouple an abstraction from its implementation so that the two can vary independently.

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

class Abstraction
{
public:
    virtual ~Abstraction() {}
    virtual string operation() = 0;
};

class Implementor
{
public:
    virtual ~Implementor() {}
    virtual string operation_impl() = 0;
};

class Abstraction1 : public Abstraction
{
public:
    Abstraction1(Implementor * impl): impl{impl} {}
   ~Abstraction1() { delete impl; }
    string operation() override
    {
        return "Abstraction1: Delegating implementation to an implementor. -> "
            + impl->operation_impl();
    }

private:
    Implementor * impl;
};

class Implementor1 : public Implementor
{
public:
    string operation_impl()
    {
        return "Implementor1: Hello World1!";
    }
};

int main()
{
    Abstraction * abstraction = new Abstraction1(new Implementor1);
    print_message("", abstraction->operation());
    delete abstraction;
}

```

Composite
---------
Compose objects into tree structures to represent part-whole hierarchies.
Composite lets clients treat individual objects and compositions of objects uniformly.

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

class Component
{
public:
    explicit Component(string const & name): name{name} {}
    virtual ~Component() {}
    virtual string operation() = 0;
    virtual void add(Component *) = 0;
    string const & get_name() const { return name; }

private:
    string name;
};

class Leaf : public Component
{
public:
    using Component::Component;
    string operation() override
    {
        return get_name();
    }
    void add(Component *) override {}
};

class Composite : public Component
{
public:
    using Component::Component;
    ~Composite() override
    {
        for (auto child : children) {
            delete child;
        }
    }
    string operation() override
    {
        string s = get_name();
        for (auto child : children) {
            s += "(" + child->operation() + ")";
        }
        return s;
    }
    void add(Component * c) override
    {
        children.push_back(c);
    }

private:
    vector<Component *> children;
};

class Client
{
public:
    static void main()
    {
        Component * composite2 = new Composite("composite2");
        composite2->add(new Leaf("leaf3"));
        composite2->add(new Leaf("leaf4"));
        composite2->add(new Leaf("leaf5"));
        Component * composite1 = new Composite("composite1");
        composite1->add(new Leaf("leaf1"));
        composite1->add(composite2);
        composite1->add(new Leaf("leaf2"));

        print_message("(1)", composite1->operation());
        print_message("(2)", composite2->operation());

        delete composite1;
    }
};

int main()
{
    Client::main();
}

```

Decorator
---------
Attach additional responsibilities to an object dynamically.
Decorators provide a flexible alternative to subclassing for extending functionality.

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

class Component
{
public:
    virtual ~Component() {}
    virtual string operation() = 0;
};

class Component1 : public Component
{
public:
    string operation() override
    {
        return "Hello World from Component1!";
    }
};

class Decorator : public Component
{
public:
    Decorator(Component * c): component_ptr{c} {}
   ~Decorator() override { delete component_ptr; }
    string operation() override
    {
        return component_ptr->operation();
    }
private:
    Component * component_ptr = nullptr;
};

class Decorator1 : public Decorator
{
public:
    using Decorator::Decorator;
    string operation() override
    {
        return add_behavior(Decorator::operation());
    }
    string add_behavior(string const & s)
    {
        return "***" + s + "***";
    }
};

class Decorator2 : public Decorator
{
public:
    using Decorator::Decorator;
    string operation() override
    {
        return add_behavior(Decorator::operation());
    }
    string add_behavior(string const & s)
    {
        return " --- " + s + " --- ";
    }
};

class Client
{
public:
    static void main()
    {
        Component * component = new Component1();
        print_message("(1)", component->operation());
        component = new Decorator1(new Decorator2(component));
        print_message("(2)", component->operation());
        delete component;
    }
};

int main()
{
    Client::main();
}

```

Facade
------
Provide an unified interface to a set of interfaces in a subsystem.
Facade defines a higher-level interface that makes the subsystem easier to use.

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

class Class1
{
public:
    string operation1()
    {
        return "Class1 ";
    }
};

class Class2
{
public:
    string operation2()
    {
        return "Class2 ";
    }
};

class Class3
{
public:
    string operation3()
    {
        return "Class3 ";
    }
};

class Facade
{
public:
    virtual ~Facade() {}
    virtual string operation() = 0;
};

class Facade1 : public Facade
{
public:
    Facade1(Class1 * o1, Class2 * o2, Class3 * o3):
        object1{o1}, object2{o2}, object3{o3} {}

   ~Facade1() override
    {
        delete object1;
        delete object2;
        delete object3;
    }

    string operation() override
    {
        return "Facade forwards operation to ... "
                + object1->operation1()
                + object2->operation2()
                + object3->operation3();
    }

private:
    Class1 * object1;
    Class2 * object2;
    Class3 * object3;
};

class Client
{
public:
    static void main()
    {
        Facade * facade = new Facade1(new Class1(), new Class2(), new Class3());
        print_message("Facade", facade->operation());
        delete facade;
    }
};

int main()
{
    Client::main();
}

```

Flyweight
---------
Use sharing to support large numbers of fine-grained objects efficiently.

```C++
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <unordered_map>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

class Flyweight
{
public:
    virtual ~Flyweight() {}
    virtual string operation(int extrinsic_state) = 0;
};

class Flyweight1 : public Flyweight
{
public:
    Flyweight1(string const & intrinsic_state): intrinsic_state{intrinsic_state} {}
    string operation(int extrinsic_state) override
    {
        stringstream s;
        s << "performing an operation on the flyweight with intrinsic state = " << intrinsic_state
          << " and passed in extrinsic state = " << to_string(extrinsic_state) << ".";
        return s.str();
    }

private:
    string intrinsic_state;
};

class FlyweightFactory
{
public:
    static FlyweightFactory * get_instance()
    {
        static FlyweightFactory flyweight_factory;
        return & flyweight_factory;
    }

    Flyweight * get_flyweight(string const & key)
    {
        if (flyweights.find(key) == flyweights.end()) {
            print_message("Creating", "a flyweight with key = " + key);
            flyweights[key] = new Flyweight1(key);
        }
        else {
            print_message("Sharing", "a flyweight with key = " + key);
            flyweights[key] = new Flyweight1(key);
        }
        return flyweights[key];
    }

    auto get_size() { return flyweights.size(); }

private:
    FlyweightFactory() = default;
    unordered_map<string, Flyweight *> flyweights;
};

class Client
{
public:
    static void main()
    {
        FlyweightFactory * flyweight_factory = FlyweightFactory::get_instance();
        Flyweight * flyweight = nullptr;
        flyweight = flyweight_factory->get_flyweight("A");
        print_message("", flyweight->operation(100));
        flyweight = flyweight_factory->get_flyweight("A");
        print_message("", flyweight->operation(200));
    }
};

int main()
{
    Client::main();
}

```

Proxy
-----
Provide a surrogate or placeholder for another object to control access to it.

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

class Subject
{
public:
    virtual ~Subject() {}
    virtual string operation() = 0;
};

class RealSubject : public Subject
{
public:
    string operation() override
    {
        return "RealSubject!";
    }
};

class Proxy : public Subject
{
public:
    Proxy(RealSubject * r): subject{r} {}
   ~Proxy() override { delete subject; }
    string operation() override
    {
        return "Hello World from Proxy and " + subject->operation();
    }
private:
    RealSubject * subject;
};


class Client
{
public:
    static void main()
    {
        Proxy * proxy = new Proxy(new RealSubject());
        print_message("Proxy", proxy->operation());
        delete proxy;
    }
};

int main()
{
    Client::main();
}

```

Chain of Responsibility
-----------------------
Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request.
Chain the receiving objects and pass the request along the chain until an object handles it.

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
Encapsulate a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undoable operations.

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
Given a language, define a representation for its grammar along with an interpreter that uses the representation to interpret sentences in the language.

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
Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.

```C++
#include <iostream>
#include <string>
#include <cstdio>
#include <exception>

using namespace std;

auto print_message(string const & object = "", string const & content = "") -> void
{
    string message(200,0);
    snprintf(message.data(), message.size(),
            "%10s : %s", object.data(), content.data());
    cout << message << endl;
}

template <typename Element>
class Iterator
{
public:
    virtual ~Iterator() {}
    virtual Element next() = 0;
    virtual bool has_next() = 0;
};

template <typename Element>
class Aggregate
{
public:
    virtual ~Aggregate() {}
    virtual Iterator<Element> * create_iterator() = 0;
    virtual bool add(Element const & e) = 0;
};

template <typename Element>
class Aggregate1 : public Aggregate<Element>
{
public:
    class Iterator1 : public Iterator<Element>
    {
    public:
        Iterator1(Element * base, int size) : base{base}, size{size} {}

        Element next() override
        {
            if (cursor < size) {
                return base[cursor++];
            }
            return {};
        }

        bool has_next() override
        {
            return cursor < size;
        }

    private:
        int cursor = 0;
        int size = 0;
        Element * base = nullptr;
    };

public:
    Aggregate1(int n)
    {
        if (n > N) {
            throw exception {};
        }
        capacity = n;
    }

    bool add(Element const & e) override
    {
        if (size < capacity) {
            elements[size++] = e;
            return true;
        }
        return false;
    }

    Iterator<Element> * create_iterator() override
    {
        Iterator<Element> * i = new Iterator1(elements, size);
        return i;
    }

private:
    static constexpr int N = 0xFFFF;
    int capacity = 0;
    int size = 0;
    Element elements[N];
};

class Client
{
public:
    static void main()
    {
        Aggregate<string> * aggretate = new Aggregate1<string>(5);
        aggretate->add("Element A");
        aggretate->add("Element B");
        aggretate->add("Element C");

        Iterator<string> * iterator = aggretate->create_iterator();
        print_message("Client", "Traversing the aggregate front-to-back:");
        while (iterator->has_next()) {
            print_message("", iterator->next());
        }
        delete iterator;
        delete aggretate;
    }
};

int main()
{
    Client::main();
}

```

Mediator
--------
Define an object that encapsulates how a set of objects interact.
Mediator promotes loose coupling by keeping objects from referring to each other explicitly, and it lets you vary their interaction independently.

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
Without violating encapsulation, capture and externalize an object's internal state so that the object can be restored to this state later.

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
Define a one-to-many dependency between objects so that when
one object changes state, all its dependents are notified and updated automatically.

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

class Observer
{
public:
    virtual ~Observer() {}
    virtual void update() = 0;
};

class Subject
{
public:
    void attach(Observer * optr)
    {
        observers.push_back(optr);
    }

    void notify_observers()
    {
        for (auto optr : observers) {
            optr->update();
        }
    }

private:
    vector<Observer *> observers;
};

class Subject1 : public Subject
{
public:
    string const & get_state() const { return state; }
    void set_state(string const & s)
    {
        state = s;
        print_message("Subject1", "State changed to " + state);
        print_message("", "Notifying observers ...");
        notify_observers();
    }

private:
    string state;
};

class Observer1 : public Observer
{
public:
    Observer1(Subject1 * sptr): subject_ptr{sptr}
    {
        subject_ptr->attach(this);
    }

    void update() override
    {
        state = subject_ptr->get_state();
        print_message("Observer1", "State updated to : " + state);
    }

private:
    Subject1 * subject_ptr = nullptr;
    string state;
};

class Observer2 : public Observer
{
public:
    Observer2(Subject1 * sptr): subject_ptr{sptr}
    {
        subject_ptr->attach(this);
    }

    void update() override
    {
        state = subject_ptr->get_state();
        print_message("Observer2", "State updated to : " + state);
    }

private:
    Subject1 * subject_ptr = nullptr;
    string state;
};

int main()
{
    Subject1 subject1;
    Observer1 observer1(&subject1);
    Observer2 observer2(&subject1);
    print_message("main", "Changing state of Subject1 ... ");
    subject1.set_state("100");
}

```

State
-----
Allow an object to alter its behavior when its internal state changes.
The object will appear to change its class.

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

class Context;

class State
{
public:
    virtual string operation(Context * context) = 0;
};

class Context
{
public:
    Context(State * s) : state_ptr{s} {}
    string operation()
    {
        string s = "Context: Delegating state-specific behavior to the current State object.\n";
        return s + state_ptr->operation(this);
    }
    void set_state(State * s)
    {
        if (s != nullptr) {
            state_ptr = s;
        }
    }

private:
    State * state_ptr = nullptr;
};

class State1 : public State
{
public:
    static State1 * get_instance()
    {
        static State1 state1;
        return & state1;
    }

    string operation(Context * context);

private:
    State1() {}
};

class State2 : public State
{
public:
    static State2 * get_instance()
    {
        static State2 state2;
        return & state2;
    }

    string operation(Context * context);

private:
    State2() {}
};

string State1::operation(Context * context)
{
    string s = "    State1 : Hello World1!  Changing current state of Context to State2.";
    context->set_state(State2::get_instance());
    return s;
}

string State2::operation(Context * context)
{
    string s = "    State2 : Hello World1!  Changing current state of Context to State1.";
    context->set_state(State1::get_instance());
    return s;
}

int main()
{
    Context * context_ptr = new Context(State1::get_instance());
    print_message("(1)", context_ptr->operation());
    print_message("(2)", context_ptr->operation());
    delete context_ptr;
}

```

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

