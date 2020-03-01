Problematic perfect-forwarding constructor resolved by enable_if
----------------------------------------------------------------
```C++
#include <type_traits>
#include <iostream>

using namespace std;

class C
{
public:
    C(C const &) { cout << "cp" << endl; }
    C(C &&) { cout << "mv" << endl; }
    C() = default;

    template <typename T>
    C(typename enable_if<!is_same<T,C>::value,T>::type &&) { cout << "fw" << endl; }
};

int main()
{
    C object;
    C another_object(object);
}

```

Out-of-line definition of template template class member function
-----------------------------------------------------------------
```C++
#include <iostream>
#include <string>

template <typename T1, typename T2> class TypenameParameterizedTemplateClass {};

template <typename T1, typename T2, template <typename = T1, typename = T2> typename TT = TypenameParameterizedTemplateClass>
class TemplateParameterizedTemplateClass { public: auto echo() const -> std::string; };

template <typename T1, typename T2, template <typename = T1, typename = T2> typename TT>
auto TemplateParameterizedTemplateClass<T1,T2,TT>::echo() const -> std::string { return "Hello!"; }

int main()
{
    TemplateParameterizedTemplateClass<long,bool> object;
    std::cout << object.echo() << std::endl;
}

```

An order template using some template programming techniques
------------------------------------------------------------
```C++
#include <iostream>
using std::ostream;

template <typename price_t, typename quant_t>
class order_base
{
public:
    typedef price_t price_type;
    typedef quant_t quant_type;
    typedef enum { bid, ask } side_type;
    typedef uint32_t id_type;
    typedef order_base<price_type, quant_type> this_type;

public:
    order_base(id_type i, side_type s, price_type p, quant_type q);

public:
    template <typename price, typename quant>
    friend auto operator << (ostream & s, order_base<price,quant> const & o) -> ostream &;

private:
    id_type id_;
    side_type side_;
    price_type price_;
    quant_type quant_;
};

#define template_order_base template <typename price_t, typename quant_t>
#define typename_order_base order_base<price_t, quant_t>
#define order_base_template auto typename_order_base

template_order_base
typename_order_base::order_base(id_type i, side_type s, price_type p, quant_type q)
    : id_(i), side_(s), price_(p), quant_(q)
{}

template_order_base
auto operator << (ostream & s, typename_order_base const & o) -> ostream &
{
    s << "[" << o.id_ << ":" << o.side_ << ":" << o.price_ << ":" << o.quant_ << "]";
    return s;
}

#undef order_base_template
#undef typename_order_base
#undef template_order_base

class order : public order_base<double, long>
{
public:
    using order_base<double, long>::order_base;
};

int main()
{
    order o (0, order::side_type::bid, 100, 10);
    std::cout << o << std::endl;
}

```

Template: 'this_type' and 'base_type'
-------------------------------------
```C++
#include <type_traits>
using namespace std;

template <typename T>
class B
{
public:
    typedef T para_type;
    typedef B<para_type> this_type;
};

template <typename T>
struct D : B<T>
{
public:
    typedef T para_type;
    typedef D<para_type> this_type;
    typedef B<para_type> base_type;
};

template class B<long>;
template class D<long>;

typedef B<long> b_type;
typedef D<long> d_type;

static_assert(is_same<b_type::para_type, d_type::para_type>::value);
static_assert(is_same<b_type::this_type, d_type::base_type>::value);
static_assert(is_base_of<b_type, d_type>::value);

int main()
{}

```

Dispatch: blocks and queues
---------------------------
```C++
#include <dispatch/dispatch.h>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

int main()
{
    dispatch_queue_t main_q = dispatch_get_main_queue();
    vector<int> v(20); iota(begin(v),end(v),10);
    for (auto i : v) { dispatch_async(main_q, ^{ cout << i << ','; }); }
    dispatch_async(main_q, ^{ cout << "Hello,World!" << endl; exit(0); });
    dispatch_main();
}

```

The concept of emptiness - 'optional'
-------------------------------------
```C++
#include <iostream>
#include <optional>
#include <variant>
using namespace std;

constexpr int nullint = 0x80000000;

optional<int> get(int i)
{
    if (i == nullint) return nullopt;
    else return i;
}

int main()
{
    if (auto i = get(0x8000); i.has_value()) {
        cout << i.value() << endl;
    }
    else cout << "empty" << endl;

    cout << get(nullint).value_or(0) << endl;
}

```

Template argument for template template parameter must be a class template or type alias template
-------------------------------------------------------------------------------------------------
```C++
template <typename T1, typename T2> class TypenameParameterizedTemplateClass {};
template <typename T1, typename T2, template <typename = T1, typename = T2> typename TT = TypenameParameterizedTemplateClass>
class TemplateParameterizedTemplateClass {};

template class TypenameParameterizedTemplateClass<bool,long>;
template class TemplateParameterizedTemplateClass<bool,long>;
template class TemplateParameterizedTemplateClass<long,bool,TypenameParameterizedTemplateClass>;

int main() {}

```

Type identity transformation
----------------------------
```C++
#include <iostream>
using namespace std;

template <typename T> struct type_identity { using type = T; };
template <typename T> using type_identity_t = typename type_identity<T>::type;
template <typename T> auto f(T a, T b) -> T { return a * b; }
template <typename T> auto g(T a, typename type_identity<T>::type b) -> type_identity_t<T> { return a * b; }

int main()
{
//  cout << f(3.14, 42) << endl;    // KO
//  cout << f(42, 3.14) << endl;    // KO
    cout << g(3.14, 42) << endl;    // OK
    cout << g(42, 3.14) << endl;    // OK but lose precision
}

```

Precision loss in 'double' when timing large number
---------------------------------------------------
```C++
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    double a = 342.4 * 1e8;
    double b = 327.6 * 1e8;
    cout << "a = " << fixed << a << " = " << llrint(a) << endl;
    cout << "b = " << fixed << b << " = " << llrint(b) << endl;
}

```

Parameterization: figure out string literal size in compile-time
----------------------------------------------------------------
```C++
#include <iostream>

using namespace std;

template<size_t N> constexpr size_t size_of_string_literal(char const (&a)[N]) { return N-1; }

int main()
{
    static_assert(size_of_string_literal("HelloWorld") == 10);
}

```

Poker Suit Class
----------------
```C++
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Suit
{
public:
    using value_type = size_t;

    static constexpr size_t size = 4;
    static constexpr value_type not_value = static_cast<value_type>(-1);
    static constexpr value_type min_value = 0;
    static constexpr value_type max_value = size - 1;

public:
    static inline vector<Suit> all()
    {
        vector<Suit> all_suits;
        for (auto const & v : all_values()) {
            all_suits.emplace_back(v);
        }
        return all_suits;
    }

    static inline string const & all_names()
    {
        return names;
    }

    static inline vector<value_type> const & all_values()
    {
        if (values.size() != size) {
            for (value_type v = min_value; v <= max_value; v++) {
                values.push_back(v);
            }
        }
        return values;
    }

    static inline char name(value_type v)
    {
        return names[v];
    }

    static inline value_type value(char n)
    {
        for (auto const & v : all_values()) {
            if (name(v) == n) {
                return v;
            }
        }
        return not_value;
    }

    static inline vector<value_type> values;
    static inline string names = "CDHS";

public:
    Suit(value_type v): value_{v} {}
    Suit(char n): Suit{value(n)} {}
    Suit() = delete;

    char name() const { return name(value_); }
    value_type value() const { return value_; }

private:
    value_type value_;
};

int main()
{
    for(auto const & suit : Suit::all()) {
        cout << suit.name() << endl;
    }
    Suit s('S');
    cout << s.name() << endl;
}

```

Owner-Before relationship
-------------------------
```C++
#include <iostream>
#include <memory>

using namespace std;

struct T
{
    T(int m, int n): m{m}, n{n} {}
    int m = 0;
    int n = 0;
};

int main()
{
    auto ptr0 = make_shared<T>(1,2);

    shared_ptr<int> ptr1(ptr0, &ptr0->m);
    shared_ptr<int> ptr2(ptr0, &ptr0->n);
    cout << "(ptr1 < ptr2) = " << (ptr1 < ptr2) << endl;
    cout << "(ptr2 < ptr1) = " << (ptr2 < ptr1) << endl;
    cout << "ptr1.owner_before(ptr2) = " << ptr1.owner_before(ptr2) << endl;
    cout << "ptr2.owner_before(ptr1) = " << ptr2.owner_before(ptr1) << endl;

    weak_ptr<int> wptr1(ptr1);
    weak_ptr<int> wptr2(ptr2);
    cout << "wptr1.owner_before(wptr2) = " << wptr1.owner_before(wptr2) << endl;
    cout << "wptr2.owner_before(wptr1) = " << wptr2.owner_before(wptr1) << endl;
}

```

Observe shared-pointer internals
--------------------------------
```C++
#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
using namespace std;

class shared_object : public enable_shared_from_this<shared_object>
{
public:
   ~shared_object() { cout << "]"; }
    shared_object() { cout << "["; }
    shared_object(char const * s): m{s} { cout << "["; }
    shared_ptr<shared_object> get_ptr() { return shared_from_this(); }
private:
    string m;
};

template <typename Object>
void observe(weak_ptr<Object> ptr)
{
    cout << "reference(use) count: " << ptr.use_count() << "; ";
    if (ptr.expired()) return;
    ptr.lock(),
    cout << "reference(use) count: " << ptr.use_count() << "; ";
}

int main()
{
    atexit([](){ cout << endl; });
    auto ptr1 = make_shared<shared_object>();
    auto ptr2 = ptr1->get_ptr();
    observe<shared_object>(ptr1);
}
```

Inherit from fundamental types
------------------------------
```C++
#include <type_traits>

using namespace std;

int main()
{
    enum class PitchNote : unsigned int { A, B, C, D, E, F, G };
    static_assert(is_same_v<underlying_type_t<PitchNote>, unsigned int>);

    PitchNote c{PitchNote::C};
}

```

Yet another OO: Operator Overloading
------------------------------------
```C++
#include <iostream>
#include <string>

using namespace std;

class T
{
public:
   ~T() = default;
    T() = default;

    string operator()() const
    {
        return s;
    }

private:
    string s = "Hello,World!";
};

int main()
{
    T object;
    cout << object() << endl;
}

```

Tuple
-----
```C++
#include <iostream>
#include <string>

using namespace std;

template <typename T, typename ... Ts>
struct Tuple : Tuple<Ts...>
{
    Tuple(T v, Ts ... vs): Tuple<Ts...>(vs...), value(v) {}
    T value;
};

template <typename T>
struct Tuple<T>
{
    Tuple(T v): value(v) {}
    T value;
};

template <int i, typename T, typename ... Ts>
auto get(Tuple<T,Ts...> const & o)
{
    if constexpr (i == 0) { return o.value; }
    else { return get<i-1,Ts...>(o); }
}

int main()
{
    Tuple<int,double,string> o {0,1.2,"3"};
    cout << get<0>(o) << get<1>(o) << get<2>(o) << endl;
}

```

Scientific Floating-Point Number
--------------------------------
```C++
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    double micro = 1.0e-6;
    cout << micro << endl;
    cout << defaultfloat << micro << endl;
    cout << fixed << micro << endl;
    cout << scientific << micro << endl;
    cout << hexfloat << micro << endl;
}

```

Integral Constant
-----------------
```C++
#include <type_traits>

using namespace std;

int main()
{
    using I2 = integral_constant<int,2>;
    using I4 = integral_constant<int,4>;
    static_assert(I2::value * I2::value == I4::value, "2*2 != 4");
    static_assert(is_same<I2,I4>::value, "I2 != I4");

    enum class Enumeration : int { Enumerator2 = 2, Enumerator4 = 4};
    using E2 = integral_constant<Enumeration, Enumeration::Enumerator2>;
    using E4 = integral_constant<Enumeration, Enumeration::Enumerator4>;
    static_assert(E2::value * E2::value == E4::value, "2*2 != 4");
    static_assert(is_same<E2,E4>::value, "E1 != E2");
}

```

Integeral Constant and Compile-Time Loop
----------------------------------------
```C++
#include <iostream>

using namespace std;

template <int I>
struct Integer
{
    static int constexpr value = I;
};

template <int I, int N, typename F>
struct Loop
{
    static void run()
    {
        F::template visit<I>();
        Loop<I+1,N,F>::run();
    }
};

template<int N, typename F>
struct Loop<N,N,F>
{
    static void run()
    {}
};

struct Visitor
{
    template <int I>
    static void visit()
    {
        cout << I << endl;
    }
};

int main()
{
    cout << Integer<3>::value << endl;
    cout << Integer<2>::value << endl;
    cout << Integer<1>::value << endl;

    Loop<1,5,Visitor>::run();
}

```

Explicit cast to underlying type of scoped enum
-----------------------------------------------
```C++
#include <type_traits>
#include <iostream>

using namespace std;

enum class E : int { O = 1, T = 2 };
int f(int i) { return i - 1; }

template <typename E> constexpr auto to_underlying(E e) noexcept
{
    return static_cast<underlying_type_t<E>>(e);
}

int main()
{
    if (f(2) == static_cast<int>(E::T)) {
        cout << "oops" << endl;
    }
    if (f(2) == to_underlying(E::O)) {
        cout << "good" << endl;
    }
}

```

Mutual Recursion
----------------
```C++
#include <iostream>

using namespace std;

bool is_even(unsigned int n);
bool is_odd(unsigned int n);

bool is_even(unsigned int n)
{
    if (n == 0) {
        return true;
    }
    else {
        return is_odd(n - 1);
    }
}

bool is_odd(unsigned int n)
{
    if (n == 0) {
        return false;
    }
    else {
        return is_even(n - 1);
    }
}

int main()
{
    cout << is_even(8) << endl;
}

```

Parse Simple Grammar
--------------------
```C++
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <iostream>

using namespace std;

string decode(string const & code)
{
    vector<char> stack;
    for (auto c : code) {
        if (c == ']') {
            list<char> temp;

            while (stack.back() != '[') {
                temp.push_front(stack.back());
                stack.pop_back();
            }
            stack.pop_back();

            int n = stack.back() - '0';
            stack.pop_back();

            while (n--) {
                for (auto c : temp) {
                    stack.push_back(c);
                }
            }
        }
        else {
            stack.push_back(c);
        }
    }
    return string(begin(stack), end(stack));
}

int main()
{
    string s = "a3[b2[c1[d]]]e";
    cout << decode(s) << endl;
}

```

Formatted Message Creator
-------------------------
```C++
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

string message(string const & object, string const & content)
{
    string m(100, ' ');
    snprintf(m.data(), m.size(), "%10s : %s", object.data(), content.data());
    return m;
}

int main()
{
    cout << message("Factory","Produce Product") << endl;
}

```

Primality Check in Compile-Time
-------------------------------
```C++
#include <iostream>
using namespace std;

template <int N, int i>
struct PrimeTypeFunction
{
    static constexpr bool value = (N % i != 0) &&
        PrimeTypeFunction<N, i-1>::value;
};

template <int N>
struct PrimeTypeFunction<N, 1>
{
    static constexpr bool value = 1;
};

template <int A>
struct is_prime
{
    static constexpr bool value = PrimeTypeFunction<A, A-1>::value;
};

template <>
struct is_prime<0>
{
    static constexpr bool value = 0;
};

template <>
struct is_prime<1>
{
    static constexpr bool value = 0;
};

int main()
{
    static_assert(is_prime<0>::value == 0, "0 is not prime");
    static_assert(is_prime<1>::value == 0, "1 is not prime");
    static_assert(is_prime<2>::value == 1, "2 is prime");
    static_assert(is_prime<3>::value == 1, "3 is prime");

    static_assert(is_prime<13>::value == 1, "13 is prime");
    static_assert(is_prime<24>::value == 0, "24 is not prime");
}

```

Parameter Pack
--------------
```C++
#include <iostream>
#include <utility>
#include <tuple>
using namespace std;

template <typename T, T... ints>
void process_integer_sequence(integer_sequence<T, ints...>)
{
    ((cout << ints << endl),...);
}

int main()
{
    process_integer_sequence(integer_sequence<int,3,1,4,1,5>{});
}

```

'iota' function
---------------
```C++
#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v(10);
    iota(begin(v),end(v),10);
    for (auto i : v) { cout << i << endl; }
}

```

Mutable Lambda Capture
----------------------
```C++
#include <iostream>
using namespace std;
int main()
{
    [pi=3.14]() mutable {
        pi = 3.1415926;
        cout << pi << endl;
    }();
}

```

Output an integer as a character
--------------------------------
```C++
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main()
{
    cout << static_cast<char>(0x59) << endl;
    printf("%c\n",0x59);
    auto i = stoi("0x59",nullptr,16);
    cout << static_cast<char>(i) << endl;
}

```

Calculate Prices
----------------
```C++
#include <iostream>

using namespace std;

double calculate_price(int32_t price, uint32_t num_decimals = 0)
{
    double den = 1.;
    switch (num_decimals) {
        case 0: den = 1.;       break;
        case 1: den = 10.;      break;
        case 2: den = 100.;     break;
        case 3: den = 1000.;    break;
        case 4: den = 10000.;   break;
        case 5: den = 100000.;  break;
        case 6: den = 1000000.; break;
        default :
            for (auto i = 0U; i < num_decimals; i++) {
                den = den * 10;
            }
    }
    return static_cast<double>(price)/den;
}

int main()
{
    cout << calculate_price(-5) << endl;
}

```

Pass Function Template
----------------------
```C++
#include <iostream>

using namespace std;

template <typename F>
void run(F f)
{
    f();
}

void f()
{
    cout << "Function!" << endl;
}

template <typename T>
void g()
{
    cout << "Template!" << endl;
}

int main()
{
    run(f);
    run(g<int>);
}

```

Boost: Hana Heterogeneous Computation
-------------------------------------
```C++
#include <boost/hana.hpp>
#include <iostream>
#include <string>

namespace hana = boost::hana;
using namespace std;

struct T1 { string name; };
struct T2 { string name; };
struct T3 { string name; };

int main()
{
    auto heterogeneous = hana::make_tuple(T1{"1"},T2{"2"}, T3{"3"});
    hana::for_each(heterogeneous, [&](auto element){
        cout << element.name << endl;
    });
}

```

Resize: increase;decrease;
--------------------------
```C++
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct T
{
    T() { cout << "C"; }
   ~T() { cout << "D"; }
   int m = 0;
};

int main()
{
    atexit([](){ cout << endl; });
    vector<T> container;
    container.resize(20);
    container.resize(10);
    container.resize(20);
    cout << endl;
}

```

Infinity: max double value
--------------------------
```C++
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int main()
{
    cout << fixed << numeric_limits<double>::max() << endl;
}

```

Algorithm Sorting Criterion
---------------------------
```C++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v = {3,1,4,1,5};
    cout << *min_element(begin(v),end(v), [](auto const & a, auto const & b){ return a > b; }) << endl;
}

```

Order;Equal;Hash;
----------------
```C++
#include <iostream>
#include <queue>
#include <set>
#include <unordered_set>
#include <functional>

using namespace std;

struct T
{
    int a;
    int b;

    bool operator <  (T const & that) const { return a <  that.a; }
    bool operator == (T const & that) const { return b == that.b; }

    friend ostream & operator << (ostream & s, T const & o) { return s << o.a << "," << o.b; }
};

struct H
{
    size_t operator() (T const & o) const
    {
        return hash<int>{}(o.b);
    }
};

int main()
{
    priority_queue<T> q;
    q.push(T{1,1});
    q.push(T{1,2});
    q.push(T{2,1});
    q.push(T{2,2});
    while (!q.empty()) { cout << q.top() << endl; q.pop(); }
    cout << endl;

    unordered_set<T,H> s;
    s.insert(T{1,1});
    s.insert(T{2,1});
    for (auto const & e : s) { cout << e << endl; }

    auto compare = [](T const & a, T const & b){ return a.b < b.b; };
    set<T,decltype(compare)> cool_set(compare);
}

```

Priority Queue: Sorting Criterion
---------------------------------
```C++
#include <boost/hana.hpp>
#include <iostream>
#include <queue>

namespace hana = boost::hana;
using namespace std;

struct T
{
    long a = 0;
    long b = 0;

    bool operator < (T const & that) const
    {
        return a < that.a;
    }

    struct LessThan
    {
        bool operator () (T const & a, T const & b)
        {
            return a.a < b.a;
        }
    };

    friend ostream & operator << (ostream & s, T const & o)
    {
        return s << o.a << "," << o.b;
    }
};

int main()
{
    auto compare = [](T const & x, T const & y){
        return x.b < y.b;
    };

    priority_queue<T> q1;
    priority_queue<T,vector<T>,T::LessThan> q2;
    priority_queue<T,vector<T>,decltype(compare)> q3(compare);

    auto qs = hana::make_tuple(q1,q2,q3);
    hana::for_each(qs,[](auto q){
        q.push(T{1,2});
        q.push(T{2,1});
        while (!q.empty()) {
            cout << q.top() << endl;
            q.pop();
        }
    });

    return 0;
}

```

Chrono: Clock;Duration;TimePoint;
---------------------------------
```C++
#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    chrono::high_resolution_clock clock;

    auto b = clock.now();
    for (int i = 0; i < 100; i++) {
        i * i;
    }
    auto e = clock.now();

    chrono::duration<long long, nano> d {e - b};
    cout << d.count() << "(ns)" << endl;

    chrono::duration<double> seconds {e - b};
    cout << fixed << setprecision(9) << seconds.count() << "(s)" << endl;
}

```

Decompose Embedded Declaration List
-----------------------------------
```C++
#include <iostream>
#include <utility>

using namespace std;

int main()
{
    auto [_,c] = make_pair(make_pair(1,2),3);
    auto [a,b] = _;
    cout << a << b << c << endl;
}

```

Interpret Input Stream
----------------------
```C++
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main()
{
    for (string s; getline(cin,s);) {
        stringstream stream(s);
        string source;
        string target;
        double weight;
        stream >> source >> target >> weight;
        cout << source << "-" << target << ": " << weight << endl;
    }
}

#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main()
{
    string source;
    string target;
    double weight;
    while (cin >> source >> target >> weight) {
        cout << source << "-" << target << ": " << weight << endl;
    }
}

```

Inline Friends
--------------
```C++
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct T
{
    string m;
    friend ostream & operator <<(ostream & s, T & object) { return s << object.m; }
    friend istream & operator >>(istream & s, T & object) { return s >> object.m; }
};

int main()
{
    stringstream stream {"Hello!"};
    T object;
    stream >> object;
    cout << object << endl;
}

```

Test Cases
----------
```C++
#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    vector<function<bool()>> tests;
    tests.push_back([]()->bool{ return 1; });
    tests.push_back([]()->bool{ return 0; });
    assert(all_of(begin(tests),end(tests),[](auto f){ return f(); }));
}

```

Function Attributes
-------------------
```C++
[[clang::no_sanitize("address", "thread", "memory", "dataflow", "leak", "undefined"), noreturn, gnu::nothrow]] void f()
{ throw 1; }

```

decltype(auto)
--------------
```C++
string const & greet()
{
    static string s {"Hello,World!"};
    return s;
}

int main()
{
    decltype(auto) a = greet();
    cout << "const: " << is_const<remove_reference<decltype(a)>::type>::value << endl;
    cout << "  ref: " << is_reference<decltype(a)>::value << endl;

    auto b = greet();
    cout << "const: " << is_const<remove_reference<decltype(b)>::type>::value << endl;
    cout << "  ref: " << is_reference<decltype(b)>::value << endl;

    auto const & c = greet();
    cout << "const: " << is_const<remove_reference<decltype(c)>::type>::value << endl;
    cout << "  ref: " << is_reference<decltype(c)>::value << endl;
}


```

Endianness
----------
```C++
#include <arpa/inet.h>
uint32_t htonl(uint32_t);
uint32_t ntohl(uint32_t);

bool is_big_endian()
{
    return 1L == htonl(1L);
}

```

```C++
bool is_big_endian()
{
    union
    {
        uint32_t integer;
        char bytes[4];
    }
    word = {0x01020304};
    return word.bytes[0] == 0x01;
}

```

Alignment
---------
```C++
#include <iostream>

using namespace std;

int main()
{
    class T {};
    cout << alignment_of<T>::value << endl;
    cout << alignment_of<int>() << endl;
}

```

Compile-Time Computation: Factorial Numbers
-------------------------------------------
```C++
#include <iostream>

using namespace std;

inline constexpr unsigned int Factorial(unsigned int n)
{
    return n <= 1 ? n : Factorial(n-1) * n;
}

int main()
{
    cout << "Factorial(10) = " << Factorial(10) << endl;
}

```

Type Traits: Common Type
------------------------
```C++
#include <iostream>

using namespace std;

template <class T>
struct Number
{
    T n;
};

template <class T, class U>
Number<typename common_type<T,U>::type> operator+(const Number<T>& lhs,const Number<U>& rhs)
{
    return {lhs.n + rhs.n};
}

int main()
{
    Number<int> i1 = {1}, i2 = {2};
    Number<double> d1 = {2.3}, d2 = {3.5};
    cout << "i1i2: " << (i1 + i2).n << "\ni1d2: " << (i1 + d2).n << '\n' << "d1i2: " << (d1 + i2).n << "\nd1d2: " << (d1 + d2).n << '\n';
}

```

Compile-Time Recurrence: Factorial Numbers
------------------------------------------
```C++
#include <iostream>

using namespace std;

template<int n> struct Factorial
{
    static const int value = Factorial<n-1>::value * n;
};

template<> class Factorial<0>
{
    static const int value = 1;
};

int main()
{
    cout << "Factorial(5): " << Factorial<5>::value << endl;
}

```

```
g++ main.cpp -std=c++1z -Q -pipe -pthread -Ofast
```

Template and Inheritance Open Mind
----------------------------------
```C++
template<typename T> struct B {};
template<typename T> struct C {};

template<typename T> struct D : public B<D<T>> { template<typename U> void procedure(U u){}; };

template<typename T> struct D<B<T>> {};
template<typename T> struct D<C<T>> {};

int main(){}

```

Comparison between Signed and Unsigned Integers
-----------------------------------------------
```C++
#include <iostream>
#include <iomanip>
#include <functional>

using namespace std;

bool less (int a, unsigned b)
{
    if ( (a < 0) || (static_cast<unsigned>(a) < b) )
        return true;
    return false;
}

int main(int n, char * v[])
{
    int a = -1;
    unsigned b = 1u;

    cout << less(a, b) << endl;
    cout << (a < b) << endl;
    cout << less<int>()(a, b) << endl;
    cout << less<unsigned>()(a, b) << endl;
}

```

Offset of Structure Field
-------------------------
```C++
#include <stddef.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
    struct user
    {
        char name[50];
        char nick[50];
        long level;
    };

    printf("'level' is the %lu byte in 'user' structure\n", offsetof(user, level));
}

```

Decay: Array as Function Argument
---------------------------------
```C++
#include <iostream>

using namespace std;

void func(int a[2])
{
    cout << a[0] << endl;
    cout << a[1] << endl;
    cout << a[2] << endl;
}

int main()
{
    int a[3];
    func(a);
}

```

Run-Time Assert on Word Size
----------------------------
```C++
#include <iostream>
#include <iterator>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

int main()
{
    istream_iterator<string> e, i(cin);
    set<string> s;
    copy(i, e, inserter(s,s.end()));
    assert(all_of(s.begin(), s.end(), [](decltype(s)::value_type v){
        return v.size() == 5;
    }));
}

```

Precision on Stream
-------------------
```C++
#include <iostream>
#include <iomanip>

using namespace std;

int main(int n, char * v[])
try {
    cout << setw(stoi(string(v[2]))+4) << setfill('0') << fixed << setprecision(stoi(string(v[2]))) << stod(string(v[1])) << endl;
}
catch(exception & e) {
    cout << "exception: " << e.what() << endl;
    cout << "usage: " << v[0] << " double precision" << endl;
}

```

Count Words using Unique-Map
----------------------------
```C++
#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
    istream_iterator<string> e, i(cin);
    vector<string> v;
    copy(i, e, back_inserter(v));
    cout << "N = " << v.size() << endl;
    sort(v.begin(), v.end());
    unique(v.begin(), v.end());

    map<string, long> m;
    for (const auto & w : v) {
        auto p = m.find(w);
        if (p != m.end()) {
            p->second++;
        }
        else {
            m.insert(make_pair(w,1));
        }
    }

    vector<pair<long, string>> s;
    for (const auto & p : m) { s.push_back(make_pair(p.second, p.first)); }
    sort(s.begin(), s.end(), [](decltype(s)::value_type a, decltype(s)::value_type b){ return a.first > b.first; });
    for (const auto & p : s) { cout << p.first << ": " << p.second << endl; }
}

```

Stream Iterators and Transform Algorithm
----------------------------------------
```C++
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    istream_iterator<string> e,i(cin);
    ostream_iterator<string> o(cout);
    vector<string> names;
    copy(i,e,back_inserter(names));
    vector<string> lines;
    transform(names.begin(),names.end(),back_inserter(lines),[](string const & s){ return s + "\n"; });
    copy(lines.begin(),lines.end(),o);
}

```

CCIA File Name Parser
---------------------
```C++
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <tuple>
#include <sstream>
#include <cctype>

using namespace std;

int main()
{
    istream_iterator<string> e;
    istream_iterator<string> i(cin);
    ostream_iterator<string> o(cout, " ");

    vector<string> names;
    copy(i, e, back_inserter(names));

    auto seperate = [](const string & name) -> tuple<string, string, string>
    {
        string h,m,t;

        auto pu = name.find("_");
        auto pd = name.rfind(".");
        if (pu != string::npos && pd != string::npos) {
            h = name.substr(0, pu);
            m = name.substr(pu + 1, (pd - pu - 1));
            t = name.substr(pd, name.size());
        }

        return make_tuple(h,m,t);
    };

    auto align = [](string & s)
    {
        auto c = s[0];
        if (isdigit(c)) { s.insert(0, "0"); }
        if (isalpha(c)) { s[0] = toupper(c); s.insert(0, "A"); }
    };

    for (const auto & n : names) {
        stringstream stream(get<1>(seperate(n)));
        string chapter, section;
        getline(stream, chapter, '.');
        getline(stream, section, '.');

        if (max(chapter.size(), section.size()) >= 3) continue;
        if (chapter.size() == 1) { align(chapter); }
        if (section.size() == 1) { align(section); }

        cout << chapter << section << endl;
    }
}

```

Lambda: Function Procedure Thread Task
--------------------------------------
```C++
#include <iostream>
#include <thread>
#include <future>

using namespace std;

int main()
{
    // Pure Function
    {
        cout << [](int i)->int{ return i*i; }(10) << endl;
    }

    // Side-Effect Procefure
    {
        int r = 0;
        [&r](int i){ r = i*i; }(10);
        cout << r << endl;
    }

    // Thread Binds a Pure Function
    {
        thread z([](int i)->int{ return i*i; }, 10);
        z.join();
    }

    // Thread Bind a Side-Effect Procedure
    {
        int r = 0;
        thread z{[&r](int i){ r = i*i; }, 10};
        z.join();
        cout << r << endl;
    }

    // Packaged Task
    {
        packaged_task<int(int)> t{[](int i)->int{ return i*i; }};
        t(10);
        cout << t.get_future().get() << endl;
    }

    // async
    {
        auto f = async(launch::async, [](int i)->int{ return i*i; }, 10);
        cout << f.get() << endl;
    }
    return 0;
}

```

Parameterize Random Number Generation
-------------------------------------
```C++
#include <iostream>
#include <random>

using namespace std;

template <typename device = random_device,
          typename engine = default_random_engine,
          typename distribution = normal_distribution<double>>
typename distribution::result_type generate()
{
    static device dev;
    engine eng(dev());
    distribution dis;

    return dis(eng);
}

int main()
{
    for (int i = 0; i < 10; i++) cout << generate() << endl;
}

```

Bucket Exploration
------------------
```C++
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <utility>

using namespace std;

template <typename key_type, typename value_type>
ostream & operator << (ostream & s, pair<key_type,value_type> p)
{
    s << "(" << get<0>(p) << ", " << get<1>(p) << ")";
    return s;
}

template<typename unordered_container>
void print_bucket(ostream & s, unordered_container c)
{
    for (auto b = 0; b < c.bucket_count(); b++) {
        s << "[" << b << "]: ";
        for (auto i = c.begin(b); i != c.end(b); i++) {
            s << *i;
        }
        s << "\n";
    }
}

template<typename unordered_container>
void print_bucket_reverse(ostream & s, unordered_container c)
{
    for (auto i = c.begin(); i != c.end(); i++) {
        typename unordered_container::key_type key;
        if constexpr (is_same<typename unordered_container::key_type,
                              typename unordered_container::value_type>::value) {
            key = *i;
        }
        else {
            key = get<0>(*i);
        }
        s << "[" << key << "]: " << c.bucket(key) << "\n";
    }
}


int main()
{
    unordered_map<char,string> m = {{'O',"Ocean Park!"}};
    if (auto [i,r] = m.insert({'D',"Disneyland!"}); !r) {
        cout << get<0>(*i) << ": " << get<string>(*i) << endl;
    }
    print_bucket(cout, m);
    print_bucket_reverse(cout, m);

    unordered_set<string> s = {"O"};
    if (auto [i,r] = s.insert("D"); !r) {
        cout << *i << endl;
    }
    print_bucket(cout, s);
    print_bucket_reverse(cout, s);
}

```

Tree Search: `BFS` and `DFS`
---------------------------
```C++
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

template <typename vertex, typename graph = map<vertex,set<vertex>>>
graph make_graph(vector<pair<vertex,vertex>> edges)
{
    graph g;
    for (auto e : edges) g[e.first].insert(e.second);
    return g;
}

template <typename vertex, typename graph = map<vertex,set<vertex>>>
void print_graph(graph g)
{
    for (auto i = g.begin(); i != g.end(); i++)
    {
        cout << i->first << ": ";
        for (auto v : i->second) cout << v << " ";
        cout << endl;
    }
}

template <typename vertex, typename graph>
void bfs(graph & g, vertex s)
{
    queue<vertex> frontier;
    frontier.push(s);
    while (!frontier.empty())
    {
        vertex u = frontier.front();
        frontier.pop();
        for (vertex v : g[u])
        {
            frontier.push(v);
        }
        cout << u;
    }
}

template <typename vertex, typename graph>
void dfs(graph & g, vertex u)
{
    cout << u;
    for (vertex v : g[u])
    {
        dfs(g, v);
    }
}

int main()
{
    using vertex = int;
    vector<pair<vertex,vertex>> edges {
        {0,1},{0,2},
        {1,3},{1,4},{2,5},{2,6},
        {3,7},{3,8},{4,9}
    };
    using graph = map<vertex,set<vertex>>;
    graph g = make_graph<vertex>(edges);
    print_graph<vertex>(g);
    bfs(g,0); cout << endl;
    dfs(g,0); cout << endl;
}

```

