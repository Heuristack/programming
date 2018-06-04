
Lesson 01 - Iterations
=========

Triangle
--------
```C++
#include <iostream>
using namespace std;

void triangle(int n)
{
    for (auto i = 0u; i < n; i++) {
        for (auto j = 0u; j < i+1; j++) {
            cout << '*' << ' ';
        }
        cout << '\n';
    }
}

int main()
{
    triangle(4);
}
```

Symmetric Triangle
------------------
```C++
#include <iostream>
using namespace std;

void symmetric_triangle(int n)
{
    for (auto i = n; i > 0; i--) {
        for (auto j = 0; j < (n - i); j++) {
            cout << ' ' << ' ';
        }
        for (auto j = 0; j < 2*i - 1; j++) {
            cout << '*' << ' ';
        }
        cout << endl;
    }
}

int main()
{
    symmetric_triangle(4);
}
```

Lesson 02 - Arrays
=========

Rgith Rotation
--------------
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

Odd Occurrences
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

Lesson 03 - Time Complexity
=========

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

Lesson 04 - Counting Elements
=========

Counting
--------
```C++
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

vector<int> counting(vector<int> const & A, int m)
{
    vector<int> C(m+1,0);
    for (auto const & e : A) {
        C[e] += 1;
    }
    return C;
}

int main()
{
    vector<int> A = {0,0,4,2,4,5};
    auto count = counting(A,*max_element(begin(A),end(A)));
    for (auto const & e : count) { cout << e << endl; }
}
```

Swap Equal
----------
```C++
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
using namespace std;

bool is_swap_equal(vector<int> const & A, vector<int> const & B)
{
    auto sa = accumulate(begin(A),end(A),0);
    auto sb = accumulate(begin(B),end(B),0);
    for (auto i = 0u; i < A.size(); i++) {
    for (auto j = 0u; j < B.size(); j++) {
        if (sa - A[i] + B[j] == sb + A[i] - B[j]) {
            return true;
        }
    }
    }
    return false;
}

int main()
{
    vector<int> A = {3,4,5};
    vector<int> B = {3,4,5};
    cout << is_swap_equal(A,B) << endl;
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

Permutation Check
-----------------
```C++
#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> & A)
{
    int presence = 0;
    for (auto i = 0u; i < A.size(); i++) {
        presence ^= (i+1);
        presence ^= A[i];
    }
    return !presence;
}

int main()
{
    vector<int> A = {4,1,3,2};
    cout << solution(A) << endl;
}
```

Lesson 05 - Prefix Sums
=========

Prefix Partial Sum
-------------------
```C++
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int slice_sum(vector<int> const & A, int i, int j)
{
    vector<int> S(A.size(),{});
    partial_sum(begin(A),end(A),begin(S));
    if (!i) return S[j];
    return S[j] - S[i-1];
}

int main()
{
    vector<int> A = {0,1,2,3,4,5,6,7,8,9};
    cout << slice_sum(A,3,5) << endl;
}
```

Lesson 06 - Sorting
=========

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
#include <algorithm>
#include <vector>
#include <iostream>

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
#include <algorithm>
#include <vector>
#include <cassert>

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

Lesson 07 - Stacks and Queues
=========

Circular Buffer
------------
```C++
#include <iostream>
#include <vector>
#include <array>
using namespace std;

template<typename T>
class Queue
{
public:
    Queue(int n = 0): capacity{n}, storage{capacity,{}} {}

// FIXME: handle exceptional cases
    auto enqueue(T e) -> Queue & {
        storage[tail] = e;
        tail = (tail + 1) % capacity;
        return *this;
    }
    auto dequeue() -> T {
        auto e = storage[head];
        head = (head + 1) % capacity;
        return e;
    }

    int size() { return (tail - head + capacity ) % capacity; }
    int empty() { return size() == 0; }

private:
    int head = 0;
    int tail = 0;
    int capacity = 0;
    vector<T> storage;
};

int main()
{
    Queue<int> q(10);
    q.enqueue(1).enqueue(2).enqueue(3);
    cout << q.size() << endl;
    auto e = q.dequeue();
    cout << "e = " << e << endl;
    cout << q.size() << endl;
}
```

Lesson 08 - Leader
=========

Leader: `count(leader) > n/2`
-----------------------------
```C++
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int leader(vector<int> const & A)
{
    unordered_map<int,int> M;
    for (auto e : A) {
        M[e]++;
    }
    for (auto [e,n] : M) {
        if (n > A.size()/2) {
            return e;
        }
    }
    return -1;
}

int main()
{
    vector<int> A = {6,8,4,6,8,6,6};
    cout << leader(A) << endl;
}
```

Lesson 09 - Maximum Slice Problem
=========

Maximum Slice Summation
-----------------------
```C++
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int max_slice(vector<int> const & A)
{
    int maxsum = 0;
    for (unsigned i = 0; i < A.size(); i++) {
        int sum = 0;
        for (unsigned j = i; j < A.size(); j++) {
            sum += A[j];
            maxsum = max({maxsum,sum});
        }
    }
    return maxsum;
}

int main()
{
    vector<int> A = {5,-7,3,5,-2,4,-1};
    cout << max_slice(A) << endl;
}
```

Lesson 10 - Prime and Composite Numbers
=========

Count Divisors of a Number
--------------------------
```C++
#include <iostream>
using namespace std;

unsigned divisors(unsigned a)
{
    unsigned n = 0;
    unsigned i;
    for (i = 1; i * i < a; i++) {
        if (a % i == 0) {
            n += 2;
        }
    }
    if (i * i == a) {
        n += 1;
    }
    return n;
}

int main()
{
    cout << divisors(3) << endl;
    cout << divisors(4) << endl;
    cout << divisors(5) << endl;
}
```

Primality Test
--------------
```C++
#include <iostream>
using namespace std;

bool is_prime(int n)
{
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    for (int i = 1; i <= 5; i++) {
        cout << is_prime(i) << endl;
    }
}
```

Lesson 11 - Sieve of Eratosthenes
=========

Sieve
-----
```C++
#include <iostream>
#include <vector>
using namespace std;

vector<int> sieve(int n)
{
    vector<int> s(n+1,1);
    s[0] = s[1] = 0;
    for (int i = 2; i * i <= n; i++) {
        if (s[i] == 1) {
            for (int k = i * i; k <= n; k += i) {
                s[k] = 0;
            }
        }
    }
    return s;
}

int main()
{
    auto primes = sieve(17);
    for (auto i = 2u; i < primes.size(); i++) {
        if (primes[i] == 0) {
            cout << i << endl;
        }
    }
}
```

Lesson 12 - Euclidean Algorithm
=========

Euclidean algorithm by subtraction
----------------------------------
```C++
#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    if      (a < b) return gcd(a, b - a);
    else if (a > b) return gcd(a - b, b);
    else            return a;
}

int main()
{
    cout << gcd(6,9) << endl;
}
```

Euclidean algorithm by division
-------------------------------
```C++
#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    if      (a < b) return gcd(b, a);
    else if (a % b) return gcd(b, a % b);
    else            return b;
}

long long GCD(long long x, long long y)
{
    return y == 0 ? x : GCD(y, x % y);
}

int main()
{
    cout << gcd(6,9) << endl;
    cout << gcd(9,6) << endl;
    cout << GCD(6,9) << endl;
    cout << GCD(9,6) << endl;
}
```

Lesson 13 - Fibonacci Numbers
=========

Recursive Fibonacci
-------------------
```C++
#include <iostream>
using namespace std;

int fibonacci(int n)
{
    if (n <= 1) return n;
    else return fibonacci(n - 2) + fibonacci(n - 1);
}

int main()
{
    cout << fibonacci(10) << endl;
}
```

Dynamic Fibonacci
-----------------
```C++
#include <iostream>
#include <vector>
using namespace std;

int fibonacci(int n)
{
    vector<int> fib(n + 1, 0);
    fib[1] = 1;
    for (auto i = 2u; i < n + 1; i++) {
        fib[i] = fib[i-2] + fib[i-1];
    }
    return fib[n];
}

int main()
{
    cout << fibonacci(10) << endl;
}
```

Lesson 14 - Binary Search
=========

Binary Search
-------------
```C++
#include <cassert>
#include <vector>

using namespace std;

int binary_search_iterative(vector<int> & a, int e)
{
    int p = 0;
    int r = a.size();
    int d = r-p;
    int m = p+d/2;
    while (d > 0) {
        if      (e < a[m]) r = m;
        else if (e > a[m]) p = m+1;
        else return m;
        d = r-p;
        m = p+d/2;
    }
    return -1;
}

int main()
{
    vector<int> A = {1,2,3,4,5,6,7,8,9};
    for (int i = 0; i < A.size(); i++) {
        assert(binary_search_iterative(A,i+1) == i);
    }
}
```

```C++
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template<typename I, typename T>
I BinarySearch(I p, I r, T k)
{
    static auto e = r;
    for (auto d = distance(p,r); d > 0; d = distance(p,r)) {
         auto m = p + d/2;
         if (k == *m) return m;
         else if (k < *m) { r = m; }
         else if (k > *m) { p = m + 1; }
    }
    return e;
}

int main()
{
    vector<int> A = {2,3,4,5,6,8};
    auto i = BinarySearch(begin(A),end(A),5);
    if (i != A.end()) {
        cout << *i << endl;
    }
}
```

Nailing Planks
--------------
[BF:RESULT](https://app.codility.com/demo/results/trainingJMKUCA-AYF)

```C++
#include <vector>

using namespace std;

bool check(vector<int> & A, vector<int> & B, vector<int> & C, unsigned J, vector<unsigned> & mem)
{
    for (unsigned i = 0u; i < A.size(); i++) {
        if (mem[i] < J) continue;
        unsigned j;
        for (j = 0u; j <= J; j++) {
            if (A[i] <= C[j] && C[j] <= B[i]) {
                mem[i] = j;
                break;
            }
        }
        if (j > J) return false;
    }
    return true;
}

int solution(vector<int> & A, vector<int> & B, vector<int> & C)
{
    vector<unsigned> mem(A.size(),30'001);
    int p = 0;
    int r = C.size();
    int d = r-p;
    int m = p+d/2;
    int i = -1;
    while (d > 0) {
        if (check(A,B,C,m,mem)) {
            r = m;
            i = m;
        }
        else {
            p = m+1;
        }
        d = r-p;
        m = p+d/2;
    }
    if (i == -1) return i;
    else return i+1;
}

int main()
{
    vector<int> A = {1,4,5,8};
    vector<int> B = {4,5,9,10};
    vector<int> C = {4,6,7,10,12};
    cout << solution(A,B,C) << endl;
}
```

Lesson 15 - Caterpillar Method
=========

Caterpillar Method
------------------
```C++
#include <iostream>
#include <vector>
using namespace std;

bool CaterpillarMethod(vector<int> const & A, int s)
{
    int n = A.size();
    int k = 0;
    int i = 0;
    int t = 0;
    while (k < n) {
        while (i < n) {
            if (t + A[i] <= s) {
                t = t + A[i++];
                continue;
            }
            break;
        }
        if (t == s) {
            return true;
        }
        t = t - A[k++];
    }
    return false;
}

int main()
{
    vector<int> A = {6,2,7,4,1,3,6};
    cout << CaterpillarMethod(A,12) << endl;
}
```

Triangle Counting
------------------
```C++
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int triangles(vector<int> const & A)
{
    auto t = 0;
    for (auto i = 0u;    i < A.size(); i++) {
    for (auto j = i + 1; j < A.size(); j++) {
    for (auto k = j + 1; k < A.size(); k++) {
        if (A[i] + A[j] > A[k]) {
            t++;
            continue;
        }
        break;
    }
    }
    }
    return t;
}

int main()
{
    vector<int> A = {10,2,5,1,8,12};
    sort(begin(A),end(A));
    cout << triangles(A) << endl;
}
```

Triangle Counting
-----------------
```C++
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
using namespace std;

int triangles(vector<int> & A)
{
    sort(begin(A),end(A));
    auto t = 0;
    for (auto i = A.begin(); i < A.end(); i++) {
    for (auto j = next(i);   j < A.end(); j++) {
        t += lower_bound(next(j), A.end(), *i + *j) - j - 1;
    }
    }
    return t;
}

int main()
{
    vector<int> A = {10,2,5,1,8,12};
    cout << triangles(A) << endl;
}
```

Lesson 16 - Greedy Algorithms
=========

Greedy Coin Changing
--------------------
```C++
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int greedy_coin_changing(vector<int> coins, int a)
{
    vector<pair<int,int>> changes;
    for (auto i = rbegin(coins); i != rend(coins); i++) {
        changes.push_back({*i,a/(*i)});
        a = a % (*i);
    }
    for (auto [c,n] : changes) { cout << c << ":" << n << endl; }
    return accumulate(begin(changes),end(changes),0,[](auto a, auto i){
            auto [_,n] = i; return a + n;
        });
}

int main()
{
    vector<int> coins1 = {1,2,5};
    vector<int> coins2 = {1,3,4};
    auto amount = 6;
    cout << greedy_coin_changing(coins1,amount) << endl;
    cout << greedy_coin_changing(coins2,amount) << endl;
}
```

Canoeist
--------
```C++
#include <algorithm>
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

int greedy_canoesit(vector<int> weights, int maxload)
{
    auto n = weights.size();
    deque<int> fatsos;
    deque<int> skinny;
    for (auto i = 0u; i < n-1; i++) {
        if (weights[i] + weights[n-1] <= maxload) {
            skinny.push_back(weights[i]);
        }
        else {
            fatsos.push_back(weights[i]);
        }
    }
    fatsos.push_back(weights[n-1]);
#if 00
    cout << "fatsos: "; for (auto f : fatsos) cout << f; cout << endl;
    cout << "skinny: "; for (auto s : skinny) cout << s; cout << endl;
#endif
    auto canoes = 0;
    while (!fatsos.empty() || !skinny.empty()) {
        if (!skinny.empty()) {
            skinny.pop_back();
        }
        fatsos.pop_back();
        canoes++;
        if (fatsos.empty() && !skinny.empty()) {
            fatsos.push_back(skinny.back());
            skinny.pop_back();
        }
        while ((fatsos.size() > 1) && (fatsos.back() + fatsos.front() <= maxload)) {
            skinny.push_back(skinny.front());
            fatsos.pop_front();
        }
    }
    return canoes;
}

int main()
{
    vector<int> weights = {1,2,3,4};
    cout << greedy_canoesit(weights,5) << endl;
}
```

Lesson 17 - Dynamic Programming
=========

Dynamic Coin Changing
---------------------
```C++
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int dynamic_coin_changing(vector<int> coins, int a)
{
    vector<vector<int>> dp(coins.size() + 1);
    for (auto & v : dp) v.resize(a + 1, 0);
    for (auto i = 1u; i < a + 1; i++) {
        dp[0][i] = numeric_limits<int>::max();
    }

    for (auto i = 1u; i < dp.size(); i++) {
        for (auto j = 1u; j < coins[i-1]; j++) {
            dp[i][j] = dp[i-1][j];
        }
        for (auto j = coins[i-1]; j < a + 1; j++) {
            dp[i][j] = min(dp[i][j-coins[i-1]] + 1, dp[i-1][j]);
        }
    }
    return dp[coins.size()][a];
}

int main()
{
    vector<int> coins1 = {1,2,5};
    vector<int> coins2 = {1,3,4};
    auto amount = 6;
    cout << dynamic_coin_changing(coins1,amount) << endl;
    cout << dynamic_coin_changing(coins2,amount) << endl;
}
```

