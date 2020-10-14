template<typename forward_iterator>
void selection_sort(forward_iterator p, forward_iterator r)
{
    for (auto i = p; i != r; i++) {
        iter_swap(i, min_element(i,r));
    }
}

