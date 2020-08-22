#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

template <typename T>
struct Permutation
{
    Permutation(vector<T> const & S, unsigned int K): elements(S), cardinality(K)
    {
        if (cardinality > elements.size()) {
            cardinality = elements.size();
        }
    }

    auto run() -> void
    {
        backtrack(elements, 0);
    }

    auto backtrack(vector<T> S, unsigned int K) -> void
    {
        if (solution(K)) return;
        for (auto i = 0; i < S.size(); i++) {
            path.push_back(S[i]);
            auto C = S;
            C.erase(begin(C)+i);
            backtrack(C,K+1);
            path.pop_back();
        }
    }

    auto solution(unsigned int K) -> bool
    {
        if (K == cardinality) {
            for (auto const e : path) {
                cout << e;
            }
            cout << endl;
            return 1;
        }
        return 0;
    }

    vector<T> path;
    unsigned int cardinality;
    vector<T> const elements;
};

int main()
{
    vector<string> elements = {"a","b","c"};
    Permutation<string>(elements,2).run();
}

