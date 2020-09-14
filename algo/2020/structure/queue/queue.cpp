#include <iostream>
#include <list>
#include <algorithm>

namespace algo {

template <typename element_t>
class queue
{
public:
    using element_type = element_t;
    using this_type = queue<element_type>;

public:
    auto enqueue(element_type const & e) -> this_type &
    {
        data.push_back(e);
        return *this;
    }

    auto dequeue() -> element_type
    {
        auto e = data.front();
        data.pop_front();
        return e;
    }

    auto max() -> element_type
    {
        auto i = std::max_element(data.begin(),data.end());
        return *i;
    }

    auto empty() { return data.empty(); }

    auto front() { return data.front(); }
    auto back()  { return data.back();  }

private:
    std::list<element_type> data;
};

}

int main()
{
    algo::queue<int> q;
    q.enqueue(3).enqueue(1).enqueue(4).enqueue(1).enqueue(5);

    while(!q.empty()) {
        std::cout << "[" << q.front() << ":" << q.max() << "]" << std::endl;
        q.dequeue();
    }
}

