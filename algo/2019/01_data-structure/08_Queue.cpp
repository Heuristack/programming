#include <iostream>
#include <stack>
#include <list>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename T>
struct Queue
{
    auto enqueue(T const & e) -> Queue &
    {
        data.push_back(e);
        return *this;
    }

    auto dequeue() -> T
    {
        if (data.empty()) {
            throw length_error("queue is empty");
        }
        auto e = data.front();
        data.pop_front();
        return e;
    }

    auto max() -> T
    {
        auto i = max_element(begin(data),end(data));
        if (i != end(data)) {
            return *i;
        }
        else {
            throw length_error("queue is empty");
        }
    }

    bool empty()
    {
        return data.empty();
    }

    list<T> data;
};

int main()
{
    Queue<int> q;
    q.enqueue(42).enqueue(53).enqueue(31);
    cout << "max = " << q.max() << endl;
    while (!q.empty()) { cout << q.dequeue() << endl; }
}

