#include <cassert>
#include <utility>
#include <memory>

using namespace std;

template <typename Key>
struct Node
{
    Node (Key v, unique_ptr<Node<Key>> && l, unique_ptr<Node<Key>> && r) : data(v),ltree(move(l)),rtree(move(r)) {}

    Key data;
    unique_ptr<Node<Key>> ltree;
    unique_ptr<Node<Key>> rtree;
};

template <typename Key>
Node<Key> * binary_search_tree_search(unique_ptr<Node<Key>> const & r, Key k)
{
    if (r.get() == nullptr) return nullptr;
    else if (k < r->data) return binary_search_tree_search(r->ltree, k);
    else if (k > r->data) return binary_search_tree_search(r->rtree, k);
    else return r.get();
}

int main()
{
    using BST = Node<int>;
    auto tree = std::make_unique<BST>(BST{19,
                                          std::make_unique<BST>(BST{7, nullptr, nullptr}),
                                          std::make_unique<BST>(BST{43, nullptr, nullptr})
    });
    assert(tree->rtree.get() == binary_search_tree_search(tree, 43));
}

