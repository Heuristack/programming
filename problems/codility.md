
Lesson 01 - Iterations
=========

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

Lesson 08 - Leader
=========

Lesson 09 - Maximum Slice Problem
=========

Lesson 10 - Prime and Composite Numbers
=========

Lesson 11 - Sieve of Eratosthenes
=========

Lesson 12 - Euclidean Algorithm
=========

Lesson 13 - Fibonacci Numbers
=========

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

Lesson 16 - Greedy Algorithms
=========

Lesson 17 - Dynamic Programming
=========

