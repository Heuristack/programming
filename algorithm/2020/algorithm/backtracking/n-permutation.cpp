#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

#include "constraint_satisfaction_problem.hpp"

template <typename type = int>
class permutation : public constraint_satisfaction_problem<type>
{
public:
    typedef constraint_satisfaction_problem<type> base_type;

public:
    permutation(vector<type> const & values, int n)
            : base_type(values), n(n) {}

public:
    auto constraint(vector<type> const & values, size_t k) -> vector<type>;
    auto backtrack(vector<type> values) -> void override;

public:
    auto generate() -> vector<vector<type>>
    {
        backtrack(this->values);
        return permutations;
    }

private:
    vector<vector<type>> permutations;
    int n;
};

template <typename type>
auto permutation<type>::constraint(vector<type> const & values, size_t k) -> vector<type>
{
    vector<type> remaining_values;
    for (size_t i = 0; i < values.size(); i++) {
        if (i != k) {
            remaining_values.push_back(values[i]);
        }
    }
    return remaining_values;
}

template <typename type>
auto permutation<type>::backtrack(vector<type> values) -> void
{
    if (this->variables.size() == n) {
        permutations.push_back(this->variables);
    }

    for (size_t i = 0; i < values.size(); i++) {
        this->variables.push_back(values[i]);
        backtrack(constraint(values,i));
        this->variables.pop_back();
    }
}

template <typename iterator, typename inserter>
auto remove_copy_it(iterator p, iterator r, inserter b, iterator k) -> void
{
    for (auto i = p; i != r; i++) {
        if (i != k) {
            *b++ = *i;
        }
    }
}

template <typename iterator, typename return_type = vector<typename iterator_traits<iterator>::value_type>>
auto remove_copy_it(iterator p, iterator r, iterator k) -> return_type
{
    return_type v;
    remove_copy_it(p,r,back_inserter(v),k);
    return v;
}

auto generate_permutation(vector<int> s, int n) -> vector<vector<int>>
{
    static vector<vector<int>> permutations;
    static vector<int> path; // note: n-path (track) is n-permutation

    if (!n) {
        permutations.push_back(path);
        return permutations;
    }

    for (auto i = begin(s); i != end(s); i++) {
        path.push_back(*i);
        generate_permutation(remove_copy_it(begin(s),end(s),i),n-1);
        path.pop_back();
    }

    return permutations;
}


template <typename type>
ostream & operator << (ostream & strm, vector<type> const v) {
    for (auto const & s : v) {
        for (auto const & e : s) strm << e;
        strm << " ";
    }
    return strm;
}

int main()
{
    cout << permutation({1,2,3,4,5},3).generate() << endl;
    cout << generate_permutation({1,2,3,4,5},3) << endl;
}

