template <typename random_access_iterator>
void heap_sort(random_access_iterator p, random_access_iterator r)
{
    for (auto i = p; i != r; i++) push_heap(p,next(i));
    for (auto i = r; i != p; i--)  pop_heap(p,i);
}

