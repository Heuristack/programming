#define NENTRY
#include "01_InsertionSort.cpp"
#include "02_SelectionSort.cpp"
#include "03_BubbleSort.cpp"
#include "04_HeapSort.cpp"
#include "05_MergeSort.cpp"
#include "06_QuickSort.cpp"
#include <iterator>
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

using namespace std;

template<typename C, typename F>
void run(C container, F algorithm, string name)
{
    chrono::high_resolution_clock clock;
    auto b = clock.now();
    algorithm(begin(container),end(container));
    auto e = clock.now();
    is_sorted(begin(container),end(container));
    chrono::duration<long long, nano> d {e - b};
    cout << name << ":" << setw(15) << setfill('0') << d.count() << "(ns)" << endl;
}

int main()
{
    vector<int> u;
    istream_iterator<int> r, p(cin);
    copy(p, r, back_inserter(u));
    using I = decltype(u)::iterator;
    run(u,heap_sort<I>,     "H");
    run(u,merge_sort<I>,    "M");
    run(u,quick_sort<I>,    "Q");
    run(u,insertion_sort<I>,"I");
    run(u,selection_sort<I>,"S");
    run(u,bubble_sort<I>,   "B");
}

