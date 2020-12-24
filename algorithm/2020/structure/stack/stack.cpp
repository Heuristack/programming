#include <stdexcept>
#include <stack>
#include <iostream>

namespace algo {

template <typename element_t>
class stack
{
public:
    using element_type = element_t;
    using this_type = stack<element_type>;

    struct maximum_statistics
    {
        element_type max;
        int count;
    };

public:
    auto push(element_type e) -> this_type &
    {
        data.push(e);

        if ((!max_stat.empty()) && (e <= max_stat.top().max)) {
            max_stat.top().count++;
        }
        else {
            max_stat.push({e,1});
        }

        return *this;
    }

    auto pop() -> element_type
    {
        if (data.empty()) {
            throw std::length_error("empty stack");
        }

        auto e = data.top();

        if (max_stat.top().count > 1) {
            max_stat.top().count--;
        }
        else {
            max_stat.pop();
        }

        data.pop();
        return e;
    }

    auto max() -> element_type
    {
        if (max_stat.empty()) {
            throw std::length_error("empty stack");
        }
        return max_stat.top().max;
    }

    auto empty() { return data.empty(); }
    auto top() { return data.top(); }

private:
    std::stack<element_type> data;
    std::stack<maximum_statistics> max_stat;
};

}

int main()
{
    algo::stack<int> s;

    s.push(3).push(1).push(4).push(1).push(5);
    s.push(2).push(6).push(3).push(6).push(5);

    while (!s.empty()) {
        std::cout << "[" << s.top() << ":" << s.max() << "]" << std::endl;
        s.pop();
    }
}

