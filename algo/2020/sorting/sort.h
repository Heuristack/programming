#include <algorithm>
#include <iterator>

namespace {

using std::upper_bound;
using std::rotate;
using std::next;
#include "algorithm/insertion_sort.ipp"

using std::min_element;
using std::iter_swap;
#include "algorithm/selection_sort.ipp"

using std::iter_swap;
using std::next;
#include "algorithm/bubble_sort.ipp"

using std::push_heap;
using std::pop_heap;
#include "algorithm/heap_sort.ipp"

using std::distance;
using std::inplace_merge;
#include "algorithm/merge_sort.ipp"

using std::distance;
using std::partition;
#include "algorithm/quick_sort.ipp"

}

