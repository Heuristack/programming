#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct ContactList
{
    struct Equal
    {
        auto operator() (ContactList const a, ContactList const & b) const
        {
            return unordered_set<string>(begin(a.names),end(a.names))
                == unordered_set<string>(begin(b.names),end(b.names));
        }
    };

    struct Hash
    {
        auto operator() (ContactList const & c) const
        {
            size_t code;
            for (auto const & n : unordered_set<string>(begin(c.names),end(c.names))) {
                code ^= hash<string>()(n);
            }
            return code;
        }
    };

    ContactList(vector<string> const & n) : names(n) {}
    vector<string> names;
};

auto MergeContactLists(vector<ContactList> const & contacts)
{
    unordered_set<ContactList, ContactList::Hash, ContactList::Equal> unique_contacts(begin(contacts), end(contacts));
    return vector<ContactList>(begin(unique_contacts),end(unique_contacts));
}

int main()
{
    ContactList A(vector<string>{"Aureliano","Arcadio","Amaranta"});
    ContactList B(vector<string>{"Aureliano","Arcadio"});
    ContactList C(vector<string>{"Aureliano","Arcadio"});
    for (auto const & L : MergeContactLists(vector<ContactList>{A,B})) {
        for (auto const & n : L.names) {
            cout << n << " ";
        }
        cout << endl;
    }
}

