template <typename forward_iterator>
void merge_sort(forward_iterator p, forward_iterator r)
{
    if (distance(p,r) <= 1) return;
    auto m = p + distance(p,r)/2;
    merge_sort(p, m);
    merge_sort(m, r);
    inplace_merge(p, m, r);
}

