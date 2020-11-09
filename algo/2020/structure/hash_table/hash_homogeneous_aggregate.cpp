#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct contact_graph
{
    struct equal
    {
        auto operator() (contact_graph const a, contact_graph const & b) const
        {
            return unordered_set<string>(begin(a.names),end(a.names))
                == unordered_set<string>(begin(b.names),end(b.names));
        }
    };

    struct hash
    {
        auto operator() (contact_graph const & c) const
        {
            size_t code;
            for (auto const & n : unordered_set<string>(begin(c.names),end(c.names))) {
                code ^= hash<string>()(n);
            }
            return code;
        }
    };

    contact_graph(vector<string> const & n) : names(n) {}
    vector<string> names;
};

auto merge(vector<contact_graph> const & contacts)
{
    unordered_set<contact_graph, contact_graph::hash, contact_graph::equal> unique_contacts(begin(contacts), end(contacts));
    return vector<contact_graph>(begin(unique_contacts),end(unique_contacts));
}

int main()
{
    contact_graph generation1(vector<string>{"Aureliano","Arcadio","Amaranta"});
    contact_graph generation2(vector<string>{"Aureliano","Arcadio"});
    contact_graph generation3(vector<string>{"Aureliano","Arcadio"});
    for (auto const & g : merge(vector<contact_graph>{generation1,generation2,generation3})) {
        for (auto const & n : g.names) {
            cout << n << " ";
        }
        cout << endl;
    }
}

