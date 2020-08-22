***
Data Structure: Abstract Data Types
----


**Random Access Memory (RAM)**: `address -> content` in `O(1)`


**Memory Allocation Strategies**

* **RT:** dynamic on heap
* **CT:** static in data segment and automatic on stacks (in general, static)


**Data: `(Space,Relation,Time)`**

* **Continuous (objects):** relation is consistent with address, e.g., array (1-1), vector(1-1), binary heap (1-2), etc.
* **Linked (nodes):** relation is maintained in node, e.g., linked list (1-1), binary tree (1-2), rooted ordered tree (1-N), etc.
* **Ordered (partial or complete):**  `compare(key1, key2) -> bool`, e.g.,  heap (binary, Fibonacci), search tree (binary, balanced), etc. **Order-Relation: `less` `<`**
* **Distributed:** `hash(key)->address`, e.g., hash table, directed address table, etc. **Equivalence-Relation:`equal` `==`**
* **Sequential in Time (operations):** queuing theory, e.g., queue (**`FIFO`**: First-In-First-Out), stack (**`LIFO`**: Last-In-First-Out), etc.
* **Concurrent in Time (multi-threading):** partial-ordered access by multiple threads


**Operations (semantics):**

* **existence (set):** `insert` `delete` `push` `pop`
* **address (memory):** `at(address) -> content` `next` `prev` `front` `back`
* **search (content):** `find(content) -> address`
* **order statistics:** `min_element` `max_element` `minmax_element` `nth_element`

***
