template <typename forward_iterator>
void quick_sort(forward_iterator p, forward_iterator r)
{
    if (distance(p,r) <= 0) return;
    auto m = *(p + distance(p,r)/2);
    auto u = partition(p, r, [m](auto const & e){ return e <= m; });
    auto l = partition(p, u, [m](auto const & e){ return e <  m; });
    quick_sort(p, l);
    quick_sort(u, r);
}

