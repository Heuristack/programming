#include <iostream>
#include <memory>

using namespace std;

template <typename T> struct ListNode
{
    enum class TraverseOrder {B,A};
    T data;
    shared_ptr<ListNode<T>> next;
};

template <typename Key = int, typename List = shared_ptr<ListNode<Key>>>
void linked_list_traverse_recursive(List list, typename ListNode<Key>::TraverseOrder order = ListNode<Key>::TraverseOrder::PRE)
{
    if (list == nullptr) return;

    if (order == ListNode<Key>::TraverseOrder::B) cout << list->data << " ";
    linked_list_traverse_recursive(list->next, order);
    if (order == ListNode<Key>::TraverseOrder::A) cout << list->data << " ";
}

template <typename Key = int, typename List = shared_ptr<ListNode<Key>>>
void linked_list_traverse_iterative(List list)
{
    while (list) {
        cout << list->data << " ";
        list = list->next;
    }
}

template <typename Key = int, typename List = shared_ptr<ListNode<Key>>>
List linked_list_search_recursive(List list, Key key)
{
    if (list == nullptr) return nullptr;
    if (list->data == key) {
        return list;
    }
    return linked_list_search_recursive(list->next, key);
}

template <typename Key = int, typename List = shared_ptr<ListNode<Key>>>
List linked_list_search_iterative(List list, Key key)
{
    while (list && list->data != key) {
        list = list->next;
    }
    return list;
}

template <typename Key = int, typename List = shared_ptr<ListNode<Key>>>
List linked_list_remove_recursive(List list, Key key)
{
    if (list == nullptr) return nullptr;
    if (list->data == key) {
        list = list->next;
        return linked_list_remove_recursive(list, key);
    }
    list->next = linked_list_remove_recursive(list->next, key);
    return list;
}

int main()
{
    using LNI = ListNode<int>;
    auto L =
        make_shared<LNI>(LNI{1,
            make_shared<LNI>(LNI{2,
                make_shared<LNI>(LNI{3,
                    make_shared<LNI>(LNI{4,
                        nullptr})})})});

    cout << linked_list_search_recursive(L, 3) << endl;
    cout << linked_list_search_iterative(L, 3) << endl;
    cout << L->next->next << endl;

    cout << "B: "; linked_list_traverse_recursive(L, LNI::TraverseOrder::B); cout << endl;
    cout << "A: "; linked_list_traverse_recursive(L, LNI::TraverseOrder::A); cout << endl;
    cout << "I: "; linked_list_traverse_iterative(L); cout << endl;

    auto N = linked_list_remove_recursive(L, 3);
    cout << "R: "; linked_list_traverse_iterative(N); cout << endl;
    cout << "R: "; linked_list_traverse_iterative(L); cout << endl;
}

