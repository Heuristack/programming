#include <functional>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

template <typename iterator>
auto to_string(iterator b, iterator e) -> string
{
    stringstream s;
    for (auto i = b; i != e; i++) {
        s << "(" << (*i) << ")";
    }
    return s.str();
}

template <typename iterator, typename predicate>
auto partition_lower(iterator p, iterator r, predicate f)
{
    for (iterator i = p; i < r; i++) {
        if (f(*i)) {
            iter_swap(p++,i);
        }
    }
    return p;
}

template <typename iterator, typename predicate>
auto partition_upper(iterator p, iterator r, predicate f)
{
    for (iterator i = p; i < r;) {
        if (f(*i)) {
            iter_swap(--r,i);
        }
        else i++;
    }
    return r;
}

template <typename iterator, typename predicate>
auto partition_upper_lower(iterator p, iterator r, predicate f)
{
    for (iterator i = p; i < r;) {
        if (auto v = f(*i); v == 0) i++;
        else if (v < 0) iter_swap(p++,i++);
        else if (v > 0) iter_swap(i,--r);
    }
}

int main()
{
    // note : the vector to partition and the partition criterion
    vector<int> v {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9};
    auto bin_predicate = [](auto const & e) -> bool { return e > 5; };
    auto tri_predicate = [](auto const & e) -> long { return e - 5; };
    cout << to_string(begin(v),end(v)) << endl;

    // note : put target elemenets at lower locations
    partition_lower(begin(v),end(v),bin_predicate);
    cout << to_string(begin(v),end(v)) << endl;
    assert(is_partitioned(begin(v),end(v),bin_predicate));

    // note : put target elemenets at upper locations
    partition_upper(begin(v),end(v),bin_predicate);
    cout << to_string(begin(v),end(v)) << endl;
    assert(is_partitioned(begin(v),end(v),[bin_predicate](auto const & e){ return !bin_predicate(e); }));

    // note : put target elements at lower & upper locations
    partition_upper_lower(begin(v),end(v),tri_predicate);
    cout << to_string(begin(v),end(v)) << endl;
}

