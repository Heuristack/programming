#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct contact_list
{
    struct equal
    {
        auto operator() (contact_list const & a, contact_list const & b) const
        {
            return unordered_set<string>(begin(a.names),end(a.names))
                == unordered_set<string>(begin(b.names),end(b.names));
        }
    };

    struct hash
    {
        auto operator() (contact_list const & c) const
        {
            size_t code = 0;
            for (auto const & n : unordered_set<string>(begin(c.names),end(c.names))) {
                code ^= std::hash<string>()(n);
            }
            return code;
        }
    };

    explicit contact_list(vector<string> const & n) : names(n) {}
    vector<string> names;
};

auto merge(vector<contact_list> const & contacts)
{
    unordered_set<contact_list, contact_list::hash, contact_list::equal> unique_contacts(begin(contacts), end(contacts));
    return vector<contact_list>(begin(unique_contacts),end(unique_contacts));
}

int main()
{
    contact_list generation1(vector<string>{"Aureliano","Arcadio","Amaranta"});
    contact_list generation2(vector<string>{"Aureliano","Arcadio"});
    contact_list generation3(vector<string>{"Aureliano","Arcadio"});
    for (auto const & g : merge(vector<contact_list>{generation1,generation2,generation3})) {
        for (auto const & n : g.names) {
            cout << n << " ";
        }
        cout << endl;
    }
}

