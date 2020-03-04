#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct element
{
    explicit element(double m) : m(m), s(to_string(m)) {}

    struct less
    {
        bool operator () (element const & a, element const & b)
        {
            return a.s > b.s;
        }
    };

    bool operator< (element const & that) const
    {
        return m < that.m;
    }

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
        cout << pq.top().m << endl;
        pq.pop();
    }
}

int main()
{
    priority_queue<element, vector<element>, element::less> pq_s;
    priority_queue<element> pq_m;
    test(pq_s);
    test(pq_m);
}

