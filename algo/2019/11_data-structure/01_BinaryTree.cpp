#include <iostream>

using namespace std;

template <typename T>
struct BinaryTree
{
    using KeyType = T;

    struct Node
    {
        Node(KeyType k, Node * l, Node * r): data{k}, ltree{l}, rtree{r} {}
       ~Node() { if (ltree) delete ltree; if (rtree) delete rtree; }
        KeyType data;
        Node * ltree;
        Node * rtree;
    };

   ~BinaryTree() { if (root) delete root; }
    BinaryTree(Node * node): root{node} {}
    Node * root = nullptr;

    Node * search(KeyType key) { return search(key,root); }
    Node * search(KeyType key, Node * node);

    template <typename Func> void traverse(Func func) { return traverse(root,func); }
    template <typename Func> void traverse(Node * node, Func func)
    {
        if (node == nullptr) return;
        func(node->data);
        if (node->ltree) { traverse(node->ltree, func); }
        if (node->rtree) { traverse(node->rtree, func); }
    }

};

template <typename T>
typename BinaryTree<T>::Node * BinaryTree<T>::search(BinaryTree<T>::KeyType key, Node * node)
{
    if (!node) return nullptr;
    else if (key < node->data) { return search(key,node->ltree); }
    else if (key > node->data) { return search(key,node->rtree); }
    else return node;
}

int main()
{
    BinaryTree<int> tree {
        new BinaryTree<int>::Node { 1,
            new BinaryTree<int>::Node { 2,
                new BinaryTree<int>:: Node {3, nullptr, nullptr},
                new BinaryTree<int>:: Node {4, nullptr, nullptr}
            },
            new BinaryTree<int>::Node {5,
                new BinaryTree<int>:: Node {6, nullptr, nullptr},
                new BinaryTree<int>:: Node {7, nullptr, nullptr}
            }
        }
    };

    tree.traverse([](auto e) { cout << e << endl; });

    if (decltype(auto) node = tree.search(5); node) {
        cout << node->data << endl;
    }
}

