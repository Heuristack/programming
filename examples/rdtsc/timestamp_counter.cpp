#include <iostream>

using namespace std;

inline int64_t timestamp_counter()
{
    uint64_t low, high;
    asm volatile("rdtsc":"=a"(low),"=d"(high)::);
    return (high << 32) | low;
}

inline int64_t timestamp_counter_processor_id()
{
    uint64_t low, high;
    asm volatile("rdtscp":"=a"(low),"=d"(high)::);
    return (high << 32) | low;
}

int main()
{
    auto a = timestamp_counter();
    auto b = timestamp_counter();
    cout << b - a << endl;

    auto c = timestamp_counter_processor_id();
    auto d = timestamp_counter_processor_id();
    cout << d - c << endl;
}
