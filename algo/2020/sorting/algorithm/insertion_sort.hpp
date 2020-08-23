template<typename forward_iterator>
void insertion_sort(forward_iterator p, forward_iterator r)
{
    for (auto i = p; i != r; i++) {
        rotate(upper_bound(p,i,*i),i,next(i));
    }
}

