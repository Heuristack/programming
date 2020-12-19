***

Concepts
========
**Graph: vertex - edge** |
symmetry: **undirected - directed** |
edge: in - out |
degree: in - out |
weight: **unweighted - weighted** |
**adjacency** |
incidence: on - from - to |
reachability: path - subpath - simple path |
cyclicity: cyclic - acyclic - cycle |
connectivity: isolated - connected - strongly connected - **connected component** |
complete graph - bipartite graph - hypergraph |
free tree - rooted tree |
**ordered tree - positional tree** |
node: internal - external |
root - leaf |
ancestor - descendant |
parent - child - sibling |
**depth - height** |

#### Free Tree Properties
Let **`G = (V,E)`** be an **undirected graph**, the following statements are equivalent

* **`G`** is a free tree = any two vertices in **`G`** are connected by a unique simple path
* **`G`** is connected but if any edge is removed from **`E`** the resulting graph is disconnected
* **`G`** is connected and **`|E| = |V| - 1`**
* **`G`** is acyclic and **`|E| = |V| - 1`**
* **`G`** is acyclic but if any edge is added to **`E`** the resulting graph contains a cycle


Data Structures
===============
Proper graph modeling (graph data structure) is the key to making efficient use of graph algorithms, take the adjacency list for example, 
each item could be a **vertex** or an **edge** totegher with some auxiliary information like **weight**, **direction**, **out-edges**, **in-edges**, etc.

**Graph Representations:**
**`adjacency_matrix` `adjacency_list` `edge_list`**

**Graph Dimensions:**
**`directed-undirected` `weighted-unweighted` `cyclic-acyclic`**


Algorithms
==========
**`BDKPBD`**

### Search: `BFS` `DFS`
**The essence of searching** is to **follow up one option now and put the others aside for later** in an **open list** representing the searching **frontier**. 
However, to avoid algorithms **forget their history** which are doomed to repeat it, visited ones are kept in a **closed list** representing the **explored set** 
which also differentiates **graph search** from **tree search**.

**Frontier Data Structures:**
**`stack` `queue` `priority_queue`**

**Edge Classification:**
**`tree edge` `forward edge` `back edge` `cross edge`**

#### Breadth-First Search `BFS`
* Frontier: Queue
* Predecessor Subgraph: BFS Tree
* Visit Order: **Read:** Read from left to right line by line.
* Edge Classification: Tree, Cross Edge (Undirected); Tree, Back, Cross Edge (Directed)
* Shortest-Path (Unweighted):

#### Depth-First Search `DFS`
* Frontier: Stack
* Predecessor Subgraph: DFS Tree
* Visit Order: **Walk (Around: before or after):** Go along to the deepest and come back along the same way. **`PRE_ORDER` `POST_ORDER`**
* Edge Classification: Tree, Back Edge (Undirected);
* Parenthesis Structure (Directed or Undirected):
* White-Path (Directed or Undirected):

#### Searching Applications
* **Reachability**: **`PathFind`**
* **Connectivity**: **`ConnectedComponent` `StronglyConnectedComponent`**
* **Cyclicity**: Acyclic = No back edge in DFS Tree
* **Topological Sort**: DAG = Topological Order Exists. DFS Reverse PostOrder = Topological Order.


### Minimum Spanning Trees `MST`
**`Undirected`**
**`Weighted`**

**cut** - a binary partition of the vertex set.
**cross** - an edge crosses a cut if it connects the binary partition subsets.
**light** - a light edge is the minimum weighted edge crosses the cut.
**respect** - a cut respects an edge set if no edge in the set cross the cut.
**safe** - an edge is safe if it could be added into the minimum spanning tree edge subset while maintaining the invirant.


**Generic MST:**
Greedily one-by-one select then add the minimum safe edge into the minimum spanning tree edge subset.

* maintain an edge set as a subset of the minimum spanning tree
* select an safe edge and add it into the set at each iteration
* until all vertices are contained by the edge set


### Single Source Shortest Paths `SSSP`
**`Directed`**
**`Weighted`**

**relaxation:** relax shortest-path estimate according to the triangle-inequality (reduce the estimated shortest-path weight).

**Properties**

* **Optimal Substructure:** subpaths of a shortest paths are shortest paths
* **Triangle Inequallity:** For edge `(u,v)` with weight `w(u,v)`, shortest path `p(s,v) <= p(s,u) + w(u,v)`
* **Upper-Bound:**
* **No-Path:** If `p(s,t)` is infinity, there is no shortest path from `s` to `t`
* **Convergence:**
* **Path-Relaxation:**
* **Predecessor-Subgraph:**


### Events
* **Vertex Exploration:** **`discover_vertex` `finish_vertex`**
* **Edge Exploration:** **`examine_edge` `cycle_edge`**
* **Edge Classification:** **`tree_edge` `forward_edge` `cross_edge` `back_edge`**
* **Edge Relaxation:** **`edge_relaxed` `edge_minimized`**

***
