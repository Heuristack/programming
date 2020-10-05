#include <iostream>
#include <iterator>
#include <vector>

using std::cout;
using std::endl;
template <typename item> using vector_type = std::vector<item>;

template <typename item_type, typename subset_type = vector_type<item_type>, typename powerset_type = vector_type<subset_type>>
auto generate(subset_type subset) -> powerset_type
{
    powerset_type powerset;
    if (!subset.empty()) {
        item_type item = subset.back();
        subset.pop_back();
        powerset =  generate<item_type>(subset);
        for (subset_type subset : powerset_type(powerset)) {
            subset.push_back(item);
            powerset.push_back(subset);
        }
    }
    else {
        powerset.push_back(subset);
    }
    return powerset;
}

int main()
{
    for (auto subset : generate<int>({1,2,3})) {
        cout << "{";
        for (auto item : subset) {
            cout << item;
        }
        cout << "}";
        cout << endl;
    }
}

