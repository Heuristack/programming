#include <iostream>
#include <stack>
#include <exception>
#include <stdexcept>

namespace algo
{

template <typename element_t>
class stack
{
public:
    using element_type = element_t;
    using this_type = stack<element_type>;

    struct max_power { element_type max; int power; };

public:
    auto push(element_type e) -> this_type &
    {
        data.push(e);

        if ((!powers.empty()) && (e <= powers.top().max)) {
            powers.top().power++;
        }
        else {
            powers.push({e,1});
        }

        return *this;
    }

    auto pop() -> element_type
    {
        if (data.empty()) {
            throw std::length_error("empty stack");
        }

        auto e = data.top();

        if (powers.top().power > 1) {
            powers.top().power--;
        }
        else {
            powers.pop();
        }

        data.pop();
        return e;
    }

    auto max() -> element_type
    {
        if (powers.empty()) {
            throw std::length_error("empty stack");
        }
        return powers.top().max;
    }

    auto empty() { return data.empty(); }
    auto top() { return data.top(); }

private:
    std::stack<element_type> data;
    std::stack<max_power> powers;
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

