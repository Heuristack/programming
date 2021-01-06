#include <vector>
#include <queue>

#include "test_framework/generic_test.h"

using std::vector;
using std::queue;
using std::priority_queue;

vector<int> MergeSortedArrays(vector<vector<int>> const & sorted_arrays)
{
    vector<int> m;

    struct index
    {
        using iterator = vector<int>::const_iterator;
        index(iterator c, iterator e) : current(c), end(e) {}
        iterator current;
        iterator end;
        bool operator < (index const & that) const { return *current > *that.current; }
    };

    priority_queue<index> q;
    for (auto & v : sorted_arrays) {
        if (!v.empty()) {
            q.emplace(begin(v),end(v));
        }
    }
    while (!q.empty()) {
        auto i = q.top();
        q.pop();
        if (i.current != i.end) {
            m.emplace_back(*i.current);
            q.emplace(next(i.current),i.end);
        }
    }

    return m;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}

