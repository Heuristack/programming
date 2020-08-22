#include <iostream>
#include <memory>

using namespace std;

template <typename T = int>
struct BinaryTreeNode
{
    enum class TraverseOrder { B = -1, I = 0, A = 1 };
    T data;
    unique_ptr<BinaryTreeNode<T>> ltree, rtree;
};

template <typename T = int>
void binary_tree_traverse(unique_ptr<BinaryTreeNode<T>> const & tree, typename BinaryTreeNode<T>::TraverseOrder order = BinaryTreeNode<T>::TraverseOrder::PR)
{
    if (tree == nullptr) return;

    cout << "(";
    if (order == BinaryTreeNode<T>::TraverseOrder::B) cout << tree->data;
    binary_tree_traverse(tree->ltree, order);
    if (order == BinaryTreeNode<T>::TraverseOrder::I) cout << tree->data;
    binary_tree_traverse(tree->rtree, order);
    if (order == BinaryTreeNode<T>::TraverseOrder::A) cout << tree->data;
    cout << ")";
}

int main()
{
    using BTI = BinaryTreeNode<int>;
    auto EoPI_Figure_6_1_I =
    make_unique<BTI>(BTI{314,
        make_unique<BTI>(BTI{6,
            make_unique<BTI>(BTI{271,
                make_unique<BTI>(BTI{28,nullptr,nullptr}),
                make_unique<BTI>(BTI{0,nullptr,nullptr})}),
            make_unique<BTI>(BTI{561,
                nullptr,
                make_unique<BTI>(BTI{3,
                    make_unique<BTI>(BTI{17,nullptr,nullptr}),
                    nullptr})})}),
        make_unique<BTI>(BTI{6,
            make_unique<BTI>(BTI{2,
                nullptr,
                make_unique<BTI>(BTI{1,
                    make_unique<BTI>(BTI{401,
                        nullptr,
                        make_unique<BTI>(BTI{641,nullptr,nullptr})
                    }),
                    make_unique<BTI>(BTI{257,nullptr,nullptr})})}),
            make_unique<BTI>(BTI{271,
                nullptr,
                make_unique<BTI>(BTI{28,nullptr,nullptr})
            })})
    });

    using BTC = BinaryTreeNode<char>;
    auto EoPI_Figure_6_1_C =
    make_unique<BTC>(BTC{'A',
        make_unique<BTC>(BTC{'B',
            make_unique<BTC>(BTC{'C',
                make_unique<BTC>(BTC{'D',nullptr,nullptr}),
                make_unique<BTC>(BTC{'E',nullptr,nullptr})}),
            make_unique<BTC>(BTC{'F',
                nullptr,
                make_unique<BTC>(BTC{'G',
                    make_unique<BTC>(BTC{'H',nullptr,nullptr}),
                    nullptr})})}),
        make_unique<BTC>(BTC{'I',
            make_unique<BTC>(BTC{'J',
                nullptr,
                make_unique<BTC>(BTC{'K',
                    make_unique<BTC>(BTC{'L',
                        nullptr,
                        make_unique<BTC>(BTC{'M',nullptr,nullptr})
                    }),
                    make_unique<BTC>(BTC{'N',nullptr,nullptr})})}),
            make_unique<BTC>(BTC{'O',
                nullptr,
                make_unique<BTC>(BTC{'P',nullptr,nullptr})
            })})
    });

    auto const & tree = EoPI_Figure_6_1_C;
    cout << "B: "; binary_tree_traverse(tree, BTC::TraverseOrder::B); cout << endl;
    cout << "I: "; binary_tree_traverse(tree, BTC::TraverseOrder::I); cout << endl;
    cout << "A: "; binary_tree_traverse(tree, BTC::TraverseOrder::A); cout << endl;
}

