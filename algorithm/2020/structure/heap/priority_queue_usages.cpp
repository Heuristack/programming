#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct element
{
public:
    explicit element(double m) : m(m), s(to_string(m)) {}

public:
    struct greater
    {
        bool operator () (element const & a, element const & b)
        {
            return a.s > b.s;
        }
    };

    bool operator < (element const & that) const
    {
        return m < that.m;
    }

public:
    double m;
    string s;
};

template <typename priority_queue_t>
auto test(priority_queue_t & pq)
{
    pq.emplace(3.0);
    pq.emplace(1.0);
    pq.emplace(4.0);
    while (!pq.empty()) {
        cout << "(" << pq.top().m << ")";
        pq.pop();
    }
    cout << endl;
}

int main()
{
    priority_queue<element, vector<element>, element::greater> pq_s;
    priority_queue<element> pq_m;
    test(pq_s);
    test(pq_m);
}

