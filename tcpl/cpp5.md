5 Programming C++: Standard Template Library
============================================


Mnemonics
=========
* **`[SESE = Standard-Exception & System-Error]`**
* **`[CIFA = Containers Iterators Functors Algorithms]`**
* **`[LMNR = Limmits Mathematics Numerics Randoms]`**
* **`[CCSR = Character-Classification String Regex]`**
* **`[IOSB = IO Streams & Buffers]`**
* **`[UTMR = Utilities Time Memory Resources]`**
* **`[MSR = Match Search Replace]`**
* **`[DED = Devices Engines Destributions]`**
* **`[VUB = Void Unary Binary]`**
* **`[PFP = Procedure Function Predicate]`**
* **`[UBPNS = Uniform Bernoulli Poisson Normal Sampling]`**
* **`[IOFBR = Input Ouput Forward Bidirectional Random]`**
* **`3.1415926-5358979`**
* **`2.7182818-2845904`**
* **`1.6180339-8874989`**


Headers
=======
* `[exception][stdexcept][cerrno][system_error]`
* `[bitset]`
* `[array][vector][deque][forward_list][list][set][map][unordered_set][unordered_map]`
* `[stack][queue]`
* `[iterator][functional]`
* `[algorithm]`
* `[limits][cmath][numeric][random]`
* `[cctype][string][regex]`
* `[ios][istream][ostream][iostream][iomanip][sstream][fstream][streambuf]`
* `[utility][ratio][chrono][ctime][memory][scopped_allocator]`
* `[typeinfo][typeindex][type_traits]`
* `[tuple][any][optional][variant]`
* `[cerrno][cassert][csetjmp]`
* `[climits][cfloat][cmath]`
* `[cctype][cstring]`
* `[ctime]`
* `[cstddef][cstdarg][cstdio][cstdlib]`


Naming
======
* `iterator: i,o,f,b,r`
* `sequence: [p,r) or [p,q] (p == r: zero element)(p == q: one element)`
* `middle: m = (upper_m = p + distance(p,r)/2) or (lower_m = p + distance(p,q)/2)`
* `bounds: l (lower_bound), u (upper_bound)`
* `function object: {v,u,b} x {proc,pred,func}`
* `device: d`
* `engine: e`
* `distribution: d = {u,b,p,n,s}`
* `stream: s, strm, m`
* `string: s, strn, a (alpha)`
* `array:  a, arr`
* `vector: v, vec`
* `deque:  d, deq`
* `set:    s, {tr,hs}s, set, {tree_, hash_}set`
* `map:    m, {tr,hs}m, map, {tree_, hash_}map`
* `stack:  s, lifo`
* `queue:  q, fifo`


Concepts
========
* `Erasable DefaultInsertable CopyInsertable MoveInsertable EmplaceConstructible`
* `Container SequenceContainer ContiguousContainer AssociativeContainer ReversibleContainer AllocatorAwareContainer`
* `Allocator`
* `Hash`
* `Iterator InputIterator OutputIterator ForwardIterator BidirectionalIterator RandomAccessIterator`
* `EqualityComparable LessThanComparable`
* `FunctionObject Predicate BinaryPredicate Compare`


Traits
======


Functional Types
================
`optional`
`any`
`variant`
`pair`
`tuple`


Timepoint and Duration
======================

clock
-----
`chrono::{system_clock, steady_clock, high_resolution_clock}`

`time_point`
------------
`time_point`

duration
--------
`duration`


Memory
======


Exceptions
==========

Language Support
----------------

`logic_error`
-------------

`runtime_error`
---------------


Numetric Limits
===============

Sign
----
`is_signed`

Radix and Digits
----------------
`digits`
`digits10`
`max_digits10`

```C++
unsigned count(unsigned long long i)
{
    unsigned n = 0;
    while (i)
    {
        if (i&1) n++;
        i >>= 1;
    }
    return n;
}
```

```C++
int main()
{
    unsigned long long n = 0;
    cout << count(~n) << endl;										// 64
    cout << bitset<sizeof(decltype(n))*8>(~n).count() << endl;		// 64
    cout << numeric_limits<unsigned long long>::digits << endl;		// 64
}
```

Epsilon and Infinity
--------------------
`epsilon`
`infinity`

Min and Max
-----------
`min`
`max`

Round Style
-----------
`round_{toward_zero, to_nearest, toward_infinity, toward_neg_infinity}`


Mathematics
===========

Basic Operations
----------------
`abs`
`fabs`
`fmin`
`fmax`
`fmod`
`nanf`

Exponential
-----------
`exp`
`log`
`exp2`
`log2`

Power
-----
`pow`
`sqrt`

Trigonometrics
--------------
`sin`
`cos`
`tan`
`asin`
`acos`
`atan`

Nearest Integers
----------------
`ceil`
`floor`
`trunc`
`round`


Random Numbers and Distributions
================================

Device
------

Engines
-------

Distributions
-------------

Generate Random Numbers
-----------------------
```C++
int main()
{
	std::random_device d;
	std::default_random_engine e(d());
	std::normal_distribution<> n(0,1);
	std::cout << n(e) << std::endl;
}
```


Bit Operations
==============

`cd;cp;mv;`
-----------
* `bitset()`
* `bitset(unsigned long long)`
* `bitset(string const &)`
* `bitset(char const *)`
* `bitset(string, index, num)`

Bit Access
----------
`bool test(index);`
`bool operator[](index);`

```C++
int main()
{
    bitset<4> b("001");
    cout << b << endl;						// 0001
    for (auto i = 0; i < b.size(); i++)
    	cout << b.test(i); 					// 1000
    cout << endl;
}
```

Bit Set (`=1`) and Reset (`=0`)
-------------------------------
`set()`
`set(i)`
`reset()`
`reset(i)`

Bit Flip
--------
`flip()`
`flip(i)`

Set Value
---------
`set(i,&)`

`not;and;or;xor;`
-----------------
* `~`
* `& | ^`
* `&= |= ^=`

Left Shift and (Logical) Right Shift
------------------------------------
`<<` `<<=`
`>>` `>>=`

```C++
template <size_t N> unsigned int count(bitset<N> b)
{
	unsigned int n = 0;
	while (b.any())
	{
		// test(0): if the right most bit is set or not
		while (!b.test(0))
		{
			b >>= 1;
		}
		n++;
		b >>= 1;
	}
	return n;
}
```

```C++
unsigned long count(unsigned long u)
{
	unsigned long n = 0;
	while (u)
	{
		while (!(u&1))
		{
			u >>= 1;
		}
		n++;
		u >>= 1;
    }
    return n;
}
```

Size and Count
--------------
`size()`
`count()`

Set Predicate
-------------
`none()`
`any()`
`all()`

Type Conversions
----------------
`to_string()`
`to_ulong()`
`to_ullong()`

I/O
---
`ostream & operator <<();`
`istream & operator >>();`


Character Classification
========================
`iscntrl`
`isprint`
`isspace`
`isblank`
`ispunct`
`isdigit`
`isalpha`
`isalnum`
`islower`
`isupper`
`toupper`
`tolower`


String Operations
=================

Special Types and Values
------------------------
`traits_type;`
`static const size_type string::npos;`

`cd;cp;mv;`
-----------
* `();~();`
* `(string const &);`
* `(string &&);`
* `(char const *);`
* `(string const &, index, num);`
* `(char const *, num);`
* `(num, char);`
* `(begin, end);`
* `(initializer_list);`

`assign;insert;replace;`
------------------------

`erase;clear;resize;`
---------------------


Substring and String Concatenation
----------------------------------
`string substr(index, size);`
`string operator+ (const string &, const string &);`

```C++
if (index > size())
{
    throw out_of_range();
}
```

Comparisons
-----------
`bool comparison();`
`int compare();`

`find;find_first_of;find_last_of;`
----------------------------------

`C`-string and `char`-array
---------------------------
`c_str()`
`data()`
`copy(char * buffer, size_type size, size_type index);`

Numeric Conversions
-------------------
`int sto{i,l,ll,ul,ull,f,d,ld}(const &, index, base);`
`string to_string(value);`

`I/O`
-----
`ostream & operator<<();`
`istream & operator>>();`
`istream & getline(istream, string, delimiter);`

Allocator
---------
`string::allocator_type string::get_allocator() const;`


Regex
=====

Match
-----

Search
------

Replace
-------


Stream `I/O`
============

Class Hierarchy
---------------
`ios_base;` `basic_ios;` `basic_istream;` `basic_ostream;` `basic_iostream;`
`basic_istringstream;` `basic_ostringstream;` `basic_iostringstream;`
`basic_ifstream;` `basic_ofstream;` `basic_iofstream;`

Stream Operations
-----------------

Buffer
------

Base-N
------
`dec`
`hex`
`oct`
`setbase`

```C++
int main()
{
	constexpr int n = 1 << 31;
	std::cout << std::oct << n << std::endl;
	std::cout << std::dec << n << std::endl;
	std::cout << std::hex << n << std::endl;
}
```

Precision
---------
`setprecision`

```C++
int main()
{
	using namespace std;
	const long double pi = acos(-1.L);
	cout << setprecision(numeric_limits<long double>::digits10+1) << pi << endl;
}
```

Time
----
`get_time`
`put_time`

Money
-----
`get_money`
`put_money`

Quote a String
--------------
```C++
int main()
{
	std::string a = "Hello,World!";
	std::cout << std::quoted(a) << std::endl;    // "Hello,World!"
}
```


STL Container Operations
========================

Types
-----
* `{key,value,size,difference,mapped}_type;`
* `{key,value}_compare;`
* `hasher;`
* `key_equal;`
* `{const}{pointer,reference,{reverse,local}_iterator}`
* `node_type; [since C++17]`
* `insert_return_type; [since C++17]`

`cd;cp;mv;sw;`
--------------
* `C();~C();`
* `C(const &C);`
* `C& operator=(const &C);`
* `C(C&&);`
* `C& operator=(C&&);`
* `C(initializer_list);`
* `C& operator=(initializer_list);`
* `C(n,&);`
* `C(begin,end);`
* `void C::swap(C&);`
* `void swap(C&,C&);`

Iterators
---------
`{c}{r}{begin,end}();`

Observers
---------
`key_comp`
`value_comp`
`key_eq`
`hash_function`

Capacity
--------
`empty`
`size`
`capacity`
`max_size`
`resize`
`reserve`
`shrink_to_fit`

Comparisons
-----------
`==`
`!=`
`<`
`<=`
`>`
`>=`

Splice and Merge (Associative Container)
----------------------------------------
`this->splice(this->position, that, that.begin, that.end);`
`this->merge(that); [since C++17]`

Element Manipulation
--------------------
`insert`
`erase`
`clear`
`{push,pop}{front,back}`
`try_emplace`
`emplace`
`emplace_hint`
`insert(node)`
`node extract(position)`
`node extrace(value)`
`insert_or_assign`

Element Access
--------------
`at`
`operator[]`
`front`
`back`

Element Search: `find;bound;range;count`
--------------------------------------------
`find`
`lower_bound`
`upper_bound`
`equal_range;`
`count`

List Operations
---------------
`reverse`
`sort`
`unique`
`remove`
`splice`

Forward List Operations
-----------------------
`insert_after`
`erase_after`
`emplace_after`
`splice_after;`

Bucket Operations
-----------------
* `bucket_index bucket(value);`
* `bucket_count;`
* `bucket_size(bucket_index);`
* `{c}{begin,end}(bucket_index);`

```C++
template<UnorderedAssociativeContainer> void traverse_bucket(UnorderedAssociativeContainer c)
{
	for (auto bucket_index = 0; bucket_index < c.bucket_count(); bucket_index++) {
		cout << "bucket [" << bucket_index << "]: ";
		for (auto i = c.begin(bucket_index); i != c.end(bucket_index); i++) {
			cout << *i << " ";
		}
		cout << endl;
	}
}
```

`map.insert(element) -> <iterator,bool>`
----------------------------------------
`[i,r] = map.insert(); [since C++17]`

```C++
std::map<std::string, std::string> m = {{"A","**"}};
if (auto [i,r] = m.insert({"A",".."}); !r) {
    std::cout << "Exist: " << get<1>(i) << std::endl;
}
```

Container Adaptors
==================

Stack
-----
`push`
`pop`
`top`
`empty`
`size`
`emplace`

Queue
-----
`push`
`pop`
`front`
`back`
`empty`
`size`
`emplace`

Priority Queue
--------------
`push`
`pop`
`top`
`empty`
`size`
`emplace`


Iterators
=========

Iterator Tags
-------------

Iterator Adaptors
-----------------

Inserters
---------

Move Iterators
--------------

Stream Iterators
----------------


STL Algorithms
==============

Prefix Semantics
----------------
`{is,partial,inplace,stable}_`

Suffix Semantics
----------------
`_{if,n,copy,backward,until}`

Fill & Generate
---------------
`fill(f,f,&);`
`fill_n(o,n,&);`
`generate(f,f,vfunc);`
`generate_n(o,n,vfunc);`

`rm;cp;mv;tr;sw`
----------------
`f remove(f,f,&);`
`o copy(i,i,o);`
`o move(i,i,o);`
`o transform(i,i,o,ufunc);`
`remove_if(f,f,upred);`
`copy_if();`
`copy_n();`
`copy_backward();`
`swap_ranges(f,f,f);`
`swap(&,&);`
`iter_swap(f,f);`

Visit
-----
`ufunc for_each(i,i,ufunc);`

Predicates
----------
`bool none_of(i,i,upred);`
`bool any_of(i,i,upred);`
`bool all_of(i,i,upred);`

Comparison
----------
`bool equal(i,i,i);`
`bool equal(i,i,i,bpred);`
`(i,i) mismatch(i,i,i);`
`(i,i) mismatch(i,i,i,bpred);`

Permutation
-----------
`bool is_permutation(f,f,f,f,bpred);`
`bool next_permutation(b,b,bpred);`
`bool prev_permutation(b,b,bpred);`

Mutation
--------
`rotate(f,f,f);`
`reverse(b,b);`
`shuffle(r,r);`

Heap
----
`push_heap(r,r,bpred);`
`pop_heap(r,r,bpred);`
`make_heap(r,r,bpred);`
`sort_heap(r,r,bpred);`
`is_heap();`
`is_heap_until();`

Merge
-----
`o merge(i,i,i,i,o,bpred);`
`inplace_merge(b,b,b,bpred);`

Partition
---------
`b partition(b,b,upred);`
`bool is_partitioned();`
`partition_point();`
`b stable_partition(b,b,upred);`
`partition_copy();`

Order Statistics
----------------
`f min_element(f,f,bpred);`
`f max_element(f,f,bpred);`
`(f,f) minmax_element(f,f,bpred);`
`& min(&,&,bpred);`
`& max(&,&,bpred);`
`(&,&) minmax(&,&,bpred);`
`& min(initializer_list,bpred);`
`& max(initializer_list,bpred);`
`(&,&) minmax(initializer_list,bpred);`
`nth_element(r,r,r,bpred);`

Sort
----
`sort(r,r,bpred);`
`stable_sort(r,r,bpred);`
`partial_sort(r,r,r,bpred);`
`is_sorted(f,f,bpred);`
`f is_sorted_until(f,f,bpred);`

Bounds & Equal Range
--------------------
`f lower_bound(f,f,&,bpred);`
`f upper_bound(f,f,&,bpred);`
`(f,f) equal_range(f,f,&,bpred);`

Unique
------
`f unique(f,f,bpred);`

Set Operations
--------------
`bool includes(i,i,i,i);`
`o set_intersection(i,i,i,i,o);`
`o set_union(i,i,i,i,o);`
`o set_difference(i,i,i,i,o);`
`o set_symmetric_difference(i,i,i,i,o);`

Element Find & Count
--------------------
`i find(i,i,&);`
`i find_if(i,i,upred);`
`f find_first_of(f,f,f,f,bpred);`
`replace(f,f,&,&);`
`replace(f,f,upred,&);`
`n count(i,i,&);`
`n count_if(i,i,upred)`

Sequence Search
---------------
`f search(f,f,f,f,bpred);`
`f search_n(f,f,n,&,bpred);`
`f find_end(f,f,f,f,bpred);`

Sum & Product
-------------
`v accumulate(i,i,v,bfunc);`

Inner Product
-------------
`v inner_product(i,i,i,v,bfunc,bfunc);`

Partial Sum & Adjacent Diff : `psum;adif`
-----------------------------------------
`o partial_sum(i,i,o,bfunc);`
`o adjecent_difference(i,i,o,bfunc);`

***

