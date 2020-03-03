#include <unordered_map>
#include <iostream>

using namespace std;

template <typename unordered_container_t>
auto print_bucket(ostream & s, unordered_container_t const & container)
{
    for (auto bucket_index = 0; bucket_index < container.bucket_count(); bucket_index++) {
        s << "bucket[" << bucket_index << "]: ";
        for (auto iterator = container.begin(bucket_index); iterator != container.end(bucket_index); iterator++) {
            s << "(" << get<0>(*iterator) << "," << get<1>(*iterator) << ")";
        }
        s << endl;
    }
}

template <typename unordered_container_t>
auto print_bucket_reverse(ostream & s, unordered_container_t const & container)
{
    for (auto iterator = container.begin(); iterator != container.end(); iterator++) {
        auto const & key = get<0>(*iterator);
        auto bucket_index = container.bucket(key);
        s << "key[" << key << "]: " << bucket_index << endl;
    }
}

int main()
{
    unordered_map<int,string> m {{4,"Banana"},{5,"Orange"}};
    if (auto [i,r] = m.insert({2,"Apple"}); !r) {
        cout << "Failed to insert, already exist [" << get<0>(*i) << ":" << get<1>(*i) << "]" << endl;
    }
    print_bucket(cout,m);
    print_bucket_reverse(cout,m);
}

