***
Sorting is Searching
--------------------
Sorting is to find a particular permutation among all permutations of a given sequence of elements, in this perspective, sorting problem could be solved by **searching** - the universal problem-solving mechanism in AI. Permutation or arrangement of elements in a collection hides an important information, i.e., the concept of position, either relative or absolute, each permutation is actually a set of **`pair <position, element>`**, so the problem can be transformed to finding out all those pairs, either brute-forcingly or systematically.

Reduction
---------
The procedure is **many-to-many (`N-N`)**, i.e., find many positions for many elements or find many elements for many positions, the key to solve such problem is to transform it to **many one-to-many (`N*1-N`)** and potentially further to **many many one-to-one (`N*N*1-1`)** problem. Here, it's just to **start** to find the element for any chosen position or find the position for any chose element, **and continue**, thinking of **mathematical induction** and **recurrence**.

Search Direction
----------------
Finding out all binary relations can be carried out in **two reverse directions**, left-to-right and right-to-left, particularly in sorting problem is to **find out the elements for each position** or reversely **find out the positions for each element**.

Assuming the input sequence is limited, given an element to find its final absolute position can be easily solved by **counting**, think the **partition** algorithm (`STL` algorithm: `partition` and `partition_point`) algorithm; however, given a position to find its element is not that easy but an **order statistics** problem, but fortunately, for extreme situations it's straight forward, i.e., find the first and last (precisely, **min** and **max**, because the order is defined by comparison operation) element (`STL` algorithm: `min_element`, `max_element`, and `minmax_element`).

Space Restriction
-----------------
When implementing these algorithms, one important consideration is whether space is restricted, i.e., **sort-in-place** (rearrange by `rotate` or `swap`, `STL` prefix `inplace_`, e.g., `inplace_merge`) or **sort-by-copy** (pass in an arbitrary collection of elements and return the ordered permutation, `STL` suffix `_copy`, e.g., `partition_copy`), or further **sort-by-move** (like sort-by-copy, but reading of the unsorted collection could be destructive).

`Iterator` Concerns
-------------------
Different sorting algorithms requre different manners in accessing the unsorted sequence, for example, insertion-sort requires to **read one element once at most** in the original sequence collection, i.e., for sort-by-copy implementation, the input could be `InputIterator` over a stream. While selection-sort has to **repeatly read elements** and expects to **remove the selected one** after each selecting iteration.

Accessing elements could be achieved by using either **iterators** or **indices**, both of which have advantages and disadvantages. By using iterators, it is possible to implement a **generic algorithm** by assuming the iterators are `ForwardIterator` so that it could be applied to all standard sequence containers, however, iterator-based ranges are **half-open** making boundary check error-prone. Constraints of `ForwardIterator` will affect some implementation details, e.g., size or distance has to be caculated by one-by-one counting because address arithematic is not allowed (only available for `RandomAccessIterator`). As a contrast, the goodness of using indexes is that algorithm implementations will be consistent with those in classic textbooks which is easy to prototype and verify its correctness. The drawback is caused by the convinence it provided, i.e., indexes can only be applied to contineous storage containers, such as built-in array, `array`, `vector` and `deque`, which generate `RandomAccessIterator` implicitly or explicitly.

High-Order Implementation
-------------------------
`STL` algorithms can also be used to express relative **high-order semantics** used by different sorting strategies, e.g., `partition` and `partition_point` can be used in quick sort for dividing the unsorted collection of elements in place, while `merge` or `inplace_merge` can be used in merge sort for combining sorted subsequences, heap algorithms like `make_heap` and `sort_heap` can be used in heap sort, and `rotate` can be used in insertion sort, etc. This will result in nice and neat implementations so called **declarative programming**.

**`ISBHMQ`**

**Insertion Sort** - **insert an arbitrary element** from the remaining unsorted sequence **into its equal range** of the increasing sorted sequence

```C++
template <typename ForwardIterator>
void insertion_sort(ForwardIterator p, ForwardIterator r)
{
    for (auto i = p; i != r; i++) {
        rotate(upper_bound(p,i,*i),i,next(i));
    }
}
```

**Selection Sort** - **move minimum element** from the remaining unsorted sequence **to its final position** in sorted sequence one after another

```C++
template <typename ForwardIterator>
void selection_sort(ForwardIterator p, ForwardIterator r)
{
    for (auto i = p; i != r; i++) {
        iter_swap(min_element(i,r), i);
    }
}
```

**Bubble Sort** - reduce **inversions** exhaustively

```C++
template <typename BidirectionalIterator>
void bubble_sort(BidirectionalIterator p, BidirectionalIterator r)
{
    for (auto j = r; j != p; j--) {
        for (auto i = p; next(i) != j; i++) {
            if (*i > *next(i)) {
                iter_swap(i, next(i));
            }
        }
    }
}
```

**Heap Sort** - push heap forward to **make heap** then pop heap backward to **sort heap**

```C++
template <typename RandomAccessIterator>
void heap_sort(RandomAccessIterator p, RandomAccessIterator r)
{
    for (auto i = p; i != r; i++) push_heap(p,i);    // make_heap(p,r);
    for (auto i = r; i != p; i--)  pop_heap(p,i);    // sort_heap(p,r);
}
```

**Merge Sort** - divide and conquer then **merge** to combine

```C++
template <typename ForwardIterator>
void merge_sort(ForwardIterator p, ForwardIterator r)
{
    if (distance(p,r) <= 1) return;
    auto m = p + distance(p,r)/2;
    merge_sort(p, m);
    merge_sort(m, r);
    inplace_merge(p, m, r);
}
```

**Quick Sort** - **partition** then conquer and no need to combine

```C++
template <typename ForwardIterator>
void quick_sort(ForwardIterator p, ForwardIterator r)
{
    if (distance(p,r) <= 0) return;
    auto m = *(p + distance(p,r)/2);
    auto u = partition(p, r, [m](auto const & e){ return e <= m; });
    auto l = partition(p, u, [m](auto const & e){ return e <  m; });
    quick_sort(p, l);
    quick_sort(u, r);
}
```

Partially Sorted
----------------
During the **execution** of these sorting algorithms, different styles of **partial sorting state** exist. For insertion and selection, the **first-half is sorted but second-half is not**. For merge sort, the first-half and second-half are **sorted separately** before merge. For quick sort, **any element in the firs-half is lower than any element in the second-half**. For heap sort, the constructed heap satisfys the **heap-property**. While for bubble sort, it seems **partially sorted randomly**.

`O(N)`
------
Sorting in **linear time** is also possible if some assumptions are hold on inputs, however, for most of them I can think of are **distribution sort**, such as counting sort, radix sort and bucket sort, etc. In short, **comparison is a binary-distribution** in terms of putting the smaller (or larger) element on left side (first position) and the other element on the other position.

***
