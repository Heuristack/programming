template <typename bidirectional_iterator>
void bubble_sort(bidirectional_iterator p, bidirectional_iterator r)
{
    for (auto j = r; j != p; j--) {
        for (auto i = p; next(i) != j; i++) {
            if (*i > *next(i)) {
                iter_swap(i, next(i));
            }
        }
    }
}

