#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

template <typename T = int>
class UnionFind : map<T,T>
{
public:
    auto Union(T a, T b) -> void
    {
        auto pa = Find(a);
        auto pb = Find(b);
        if (pa != pb) {
            this->at(pb) = pa;
        }
    }

    auto Find(T e) -> T
    {
        while (e != this->at(e)) {
            e = this->at(e);
        }
        return e;
    }

    auto Connected(T a, T b) -> bool
    {
        return Find(a) == Find(b);
    }

    auto Count() -> int
    {
        set<T> s;
        for (auto [e,g] : *this) {
            s.insert(g);
        }
        return s.size();
    }

public:
    friend auto operator << (ostream & s, UnionFind const & u) -> ostream &
    {
        for (auto [p,q] : u) {
            s << setw(6) << setfill('0') << p << ":";
            s << setw(6) << setfill('0') << q << "\n";
        }
        return s;
    }
    friend auto operator >> (istream & s, UnionFind & u) -> istream &
    {
        auto n = 0;
        s >> n;
        for (auto i = 0; i < n; i++) {
            u[i] = i;
        }
        T a;
        T b;
        while (s >> a >> b) {
            u.Union(a,b);
        }
        return s;
    }
};

int main()
{
    UnionFind<int> u;
    cin  >> u;
    cout << u;
    cout << u.Count() << endl;
}

