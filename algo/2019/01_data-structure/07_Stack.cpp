#include <iostream>
#include <stack>
#include <list>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename T>
struct Stack
{
    auto max() -> T
    {
        if (max_cache.empty()) {
            throw length_error("stack is empty");
        }
        else {
            return max_cache.top().max;
        }
    }

    auto push(T const & e) -> Stack &
    {
        data.push(e);
        if (max_cache.empty()) {
            max_cache.push({e,1});
        }
        else {
            auto current_max = max_cache.top().max;
            if (e == current_max) {
                max_cache.top().count++;
            }
            else if (e > current_max){
                max_cache.push({e,1});
            }
        }
        return *this;
    }

    auto pop() -> T
    {
        if (data.empty()) {
            throw length_error("stack is empty");
        }
        auto e = data.top();
        data.pop();
        auto current_max = max_cache.top().max;
        if (current_max == e) {
            auto & count = max_cache.top().count;
            count--;
            if (count == 0) {
                max_cache.pop();
            }
        }

        return e;
    }

    bool empty()
    {
        return data.empty();
    }

    stack<T> data;
    struct MaxCount { T max; long count; };
    stack<MaxCount> max_cache;
};

int main()
{
    Stack<int> s; s.push(42).push(53).push(31);
    cout << "max = " << s.max() << endl;
    while (!s.empty()) { cout << s.pop() << endl; }
}

