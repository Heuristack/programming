Traits
------

```C++
template <class Iterator>
struct iterator_traits {
    typedef ... iterator_category;
    typedef ... value_type;
    typedef ... difference_type;
    typedef ... pointer;
    typedef ... reference;
};

```

```C++
template<class BidirectionalIterator>
void my_reverse(BidirectionalIterator first, BidirectionalIterator last)
{
    typename std::iterator_traits<BidirectionalIterator>::difference_type n = std::distance(first, last);
    --n;
    while(n > 0) {
        typename std::iterator_traits<BidirectionalIterator>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
        n -= 2;
    }
}

```

