Missing Element
---------------
```C++
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

int solution(vector<int> & a)
{
    int presence = 0;
    for (auto i = 0; i < a.size(); i++) {
        presence ^= (i + 1);
        presence ^= a[i];
    }
    return presence ^= (a.size() + 1);
}

int main()
{
    vector<int> A = {2,3,1,5};
    cout << solution(A) << endl;
}
```

Tape Equilibrium
----------------
```C++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> & a)
{
    vector<int> s(a.size(),0);
    for (auto i = 0; i < a.size(); i++) {
        s[0] -= a[i];
    }
    for (auto i = 1; i < a.size(); i++) {
        s[i] = s[i-1] + 2*a[i-1];
    }
    for (auto i = 1; i < s.size(); i++) {
        s[i] = abs(s[i]);
    }
    return *min_element(begin(s)+1,end(s));
}

int main()
{
    vector<int> A = {3,1,2,4,3,};
    cout << solution(A) << endl;
}
```

Rgith rotate K times
--------------------
```C++
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void right_rotate(vector<int> & A)
{
    auto N = static_cast<long>(A.size());
    int t = 0;
    for (long i = N-1; i - 1 >= 0; i--) {
        if (i == N-1) { t = A[i]; }
        A[i] = A[i-1];
        if (i - 1 == 0) { A[i-1] = t; }
    }
}

vector<int> solution(vector<int> & A, int K)
{
    for (auto i = 0; i < K; i++) {
        right_rotate(A);
    }
    return A;
}

int main()
{
    vector<int> A = {3,8,9,7,6};
    auto B = solution(A,3);
    for (auto e : B) cout << e << endl;
}
```

Odd Occurencies
---------------
```C++
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

int solution(vector<int> & a)
{
    unordered_set<int> s;
    for (unsigned long i = 0; i < a.size(); i++) {
        if (s.find(a[i]) == s.end()) { s.insert(a[i]); }
        else { s.erase(a[i]); }
    }
    return *s.begin();
}
```

Maximum Product of Three
------------------------
```C++
#include <algorithm>
#include <vector>

using namespace std;

int solution(vector<int> & a)
{
    sort(begin(a),end(a));
    if (a[a.size()-1] > 0) {
        return a[a.size()-1] * max(a[0]*a[1], a[a.size()-3]*a[a.size()-2]);
    }
    else {
        return a[a.size()-1]*a[a.size()-2]*a[a.size()-3];
    }
}

int main()
{
    vector<int> A = {-3,1,2,-1,5,6};
    assert(solution(A)==60);
    vector<int> B = {-5, -6, -4, -7, -10};
    cout << solution(B) << endl;
}
```

Distinct
--------
```C++
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int solution(vector<int> & a)
{
    sort(begin(a),end(a));
    return distance(begin(a),unique(begin(a),end(a)));
}

int main()
{
    vector<int> A = {2,1,1,2,3,1};
    assert(solution(A)==3);
}
```

Triangle
--------
```C++
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int solution(vector<int> & a)
{
    sort(begin(a),end(a));
    for (long i = a.size()-1; i-2 >= 0; i--) {
        if (a[i] - a[i-1] < a[i-2]) { return 1; }
        else continue;
    }
    return 0;
}

int main()
{
    vector<int> A = {10,2,5,1,8,20};
    vector<int> B = {10,50,5,1};
    cout << solution(A) << endl;
    cout << solution(B) << endl;
}
```

Number of Intersections
-----------------------
```C++
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int solution(vector<int> & a)
{
    struct segment
    {
        long p = 0; long q = 0;
        bool operator < (segment const & that) const
        {
            return p < that.p;
        }
    };
    vector<segment> segments;
    for (long i = 0; i < a.size(); i++) {
        segments.push_back(segment{i-a[i],i+a[i]});
    }
    sort(begin(segments),end(segments));

    int n = 0;
    for (long i = 0; i < segments.size(); i++) {
        for (long j = i+1; j < segments.size(); j++) {
            if (segments[j].p <= segments[i].q) {
                if (n++ > 10'000'000) return -1;
            }
            else break;

        }
    }

    return n;
}

int main()
{
    vector<int> A = {1,2'147'483'647,0};
    assert((solution(A)==2));
}
```

Missing Posative
----------------
```C++
#include <algorithm>
#include <set>
int missing(vector<int> & a)
{
    set<int> s(begin(a),end(a));
    auto first = find_if(begin(s),end(s),[](auto e){ return e > 0; });
    if (first == end(s)) {
        return 1;
    }
    auto minp = *first;
    if (minp > 1) {
        return 1;
    }
    for (auto i = first; i != end(s); i++) {
        if (*i == minp) {
            minp++;
        }
    }
    return minp;
}
```

Sliding-Puzzle: 2x3
-------------------
`Not Finished Yet`
```C++
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    using Board = vector<vector<int>>;

    int slidingPuzzle(vector<vector<int>>& board) {
        vector<Board> solution;
        heuristic_search(board, solution);
        if (solution.size() == 0) return -1;
        else return static_cast<int>(solution.size());
    }

    auto is_goal(Board & board) -> bool
    {
        auto k = 1;
        for (auto i = 0; i < M; i++) {
            for (auto j = 0; j < N; j++) {
                if (i == M-1 && j == N-1) k = 0;
                if (board[i][j] == k++) continue;
                else return false;
            }
        }
        return true;
    }

    auto locate(Board & board) -> pair<int,int>
    {
        for (auto i = 0; i < M; i++) {
            for (auto j = 0; j < N; j++) {
                if (board[i][j] == 0) {
                    return {i,j};
                }
            }
        }
        return {M,N};
    }

    enum class Direction { Up, Down, Left, Right, U = Up, D = Down, L = Left, R = Right};
    auto move(Board & board, Direction d) -> Board
    {
        Board next(board);
        auto position = locate(next);
        auto i = position.first;
        auto j = position.second;
        if (Direction::U == d) { if (i != 1-1) { swap(next[i][j],next[i-1][j]); } }
        if (Direction::D == d) { if (i != M-1) { swap(next[i][j],next[i+1][j]); } }
        if (Direction::L == d) { if (j != 1-1) { swap(next[i][j],next[i][j-1]); } }
        if (Direction::R == d) { if (j != N-1) { swap(next[i][j],next[i][j+1]); } }
        return next;
    }

    auto generate(Board & board) -> vector<Board>
    {
        vector<Board> generation;
        for (auto d : {Direction::R,Direction::D,Direction::L,Direction::U}) {
            auto next = move(board,d);
            if (next != board) {
                generation.push_back(move(board,d));
            }
        }
        return generation;
    }

    auto dfs(Board & board, bool & resolved) -> void
    {
        static vector<Board> closed;
        closed.push_back(board);

        if (is_goal(board)) {
            resolved = true;
            return;
        }

        auto generation = generate(board);
        for (auto next : generation) {
            if (!resolved) {
                if (find(begin(closed),end(closed),next) == closed.end()) {
                    dfs(next,resolved);
                }
            }
        }
    }

    auto heuristic(Board const & board) -> int
    {
        auto v = 0;
        auto k = 1;
        for (auto i = 0; i < M; i++) {
            for (auto j = 0; j < N; j++) {
                if (i == M-1 && j == N-1) k = 0;
                if (board[i][j] != k++) v++;
            }
        }
        return v;
    }

    auto heuristic_search(Board & board, vector<Board> & solution) -> void
    {
        vector<pair<Board,Board>> closed;
        auto order = [this](Board const & a, Board const & b)->bool{ return heuristic(a) > heuristic(b); };
        priority_queue<Board,vector<Board>,decltype(order)> open(order);
        open.push(board);
        while (!open.empty()) {
            auto u = open.top();
            open.pop();
            solution.push_back(u);
            if (is_goal(u)) {
                solution.push_back(u);
                return;
            }
            auto generation = generate(u);
            for (auto & v : generation) {
                if (find(begin(closed),end(closed),make_pair(v,{})) == closed.end()) {
                    open.push(v);
                }
            }
        }
    }

    int M = 2;
    int N = 3;
};

int main()
{
    vector<vector<int>> board = {{4,1,2},{5,0,3}};
    Solution solution;
    cout << solution.slidingPuzzle(board) << endl;
    vector<vector<int>> goal = {{1,2,3},{4,5,0}};
    cout << solution.is_goal(goal) << endl;
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
`179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000`

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
    cout << *min_element(begin(v),end(v),[](auto const & a, auto const & b){ return a > b; }) << endl;
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

    cout << d.count() << endl;
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
bool is_big_endian() {
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
template <class T>
struct Number
{
    T n;
};

template <class T, class U>
Number<typename std::common_type<T,U>::type> operator+(const Number<T>& lhs,const Number<U>& rhs)
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
    std::cout << "Factorial(5): " << Factorial<5>::value << std::endl;
}
//g++ main.cpp -std=c++1z -Q -pipe -pthread -Ofast
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

    std::cout << less(a, b) << std::endl;
    std::cout << (a < b) << std::endl;
    std::cout << std::less<int>()(a, b) << std::endl;
    std::cout << std::less<unsigned>()(a, b) << std::endl;
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

int main(int n, char * v[])
try {
    std::cout << std::setw(std::stoi(std::string(v[2]))+4) << std::setfill('0') << std::fixed << std::setprecision(std::stoi(std::string(v[2]))) << std::stod(std::string(v[1])) << std::endl;
}
catch(std::exception & e) {
    std::cout << "exception: " << e.what() << std::endl;
    std::cout << "usage: " << v[0] << " double precision" << std::endl;
}
```

Count Words using Unique-Map
---------------------------

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
            m.insert(std::make_pair(w,1));
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

int main()
{
    std::istream_iterator<std::string> e;
    std::istream_iterator<std::string> i(std::cin);
    std::ostream_iterator<std::string> o(std::cout, " ");

    std::vector<std::string> names;
    std::copy(i, e, std::back_inserter(names));

    auto seperate = [](const std::string & name) -> std::tuple<std::string, std::string, std::string>
    {
        std::string h,m,t;

        auto pu = name.find("_");
        auto pd = name.rfind(".");
        if (pu != std::string::npos && pd != std::string::npos) {
            h = name.substr(0, pu);
            m = name.substr(pu + 1, (pd - pu - 1));
            t = name.substr(pd, name.size());
        }

        return std::make_tuple(h,m,t);
    };

    auto align = [](std::string & s)
    {
        auto c = s[0];
        if (std::isdigit(c)) { s.insert(0, "0"); }
        if (std::isalpha(c)) { s[0] = std::toupper(c); s.insert(0, "A"); }
    };

    for (const auto & n : names) {
        std::stringstream stream(std::get<1>(seperate(n)));
        std::string chapter, section;
        std::getline(stream, chapter, '.');
        std::getline(stream, section, '.');

        if (std::max(chapter.size(), section.size()) >= 3) continue;
        if (chapter.size() == 1) { align(chapter); }
        if (section.size() == 1) { align(section); }

        std::cout << chapter << section << std::endl;
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
    //--------------
    // Pure Function
    //--------------
    {
        cout << [](int i)->int{ return i*i; }(10) << endl;
    }

    //----------------------
    // Side-Effect Procefure
    //----------------------
    {
        int r = 0;
        [&r](int i){ r = i*i; }(10);
        cout << r << endl;
    }

    //-----------------------------
    // Thread Binds a Pure Function
    //-----------------------------
    {
        thread z([](int i)->int{ return i*i; }, 10);
        z.join();
    }

    //------------------------------------
    // Thread Bind a Side-Effect Procedure
    //------------------------------------
    {
        int r = 0;
        thread z{[&r](int i){ r = i*i; }, 10};
        z.join();
        cout << r << endl;
    }

    //--------------
    // Packaged Task
    //--------------
    {
        packaged_task<int(int)> t{[](int i)->int{ return i*i; }};
        t(10);
        cout << t.get_future().get() << endl;
    }
    //------
    // async
    //------
    {
        auto f = async(std::launch::async, [](int i)->int{ return i*i; }, 10);
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

template <typename device = random_device, typename engine = default_random_engine, typename distribution = normal_distribution<double>>
typename distribution::result_type generate()
{
    static device dev;
    engine eng(dev());
    distribution dis;

    return dis(eng);
}

int main()
{
    for (int i = 0; i < 10; i++) std::cout << generate() << std::endl;
}

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

****

