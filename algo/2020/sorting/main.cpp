#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

#include "sort.h"

using namespace std;

template<typename container, typename algorithm>
void run(container vec, algorithm algo, string name)
{
    chrono::high_resolution_clock clock;
    auto b = clock.now();
    algo(begin(vec),end(vec));
    auto e = clock.now();
    chrono::duration<long long, nano> d {e - b};
    cout << name << "[" << is_sorted(begin(vec),end(vec)) << "]: "
         << setw(15) << setfill('0') << d.count() << "(ns)" << endl;
}

int main()
{
    vector<int> u;
    istream_iterator<int> r, p(cin);
    copy(p, r, back_inserter(u));
    using i = decltype(u)::iterator;
    run(u,heap_sort<i>,     "H");
    run(u,merge_sort<i>,    "M");
    run(u,quick_sort<i>,    "Q");
    run(u,insertion_sort<i>,"I");
    run(u,selection_sort<i>,"S");
    run(u,bubble_sort<i>,   "B");
}

