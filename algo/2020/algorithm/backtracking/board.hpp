template <typename element_t = int>
class board : public vector<vector<element_t>>
{
public:
    typedef vector<element_t> vector_type;
    typedef vector<vector_type> base_type;

public:
    board(int m, int n) :
        base_type(m,vector_type(n)),
        m(m),n(n) {}

    board(int n) : board(n,n) {}

public:
    int m;
    int n;
};

template <typename element_t = int>
ostream & operator << (ostream & s, board<element_t> const & b)
{
    for (int i = 0; i < b.m; i++) {
    for (int j = 0; j < b.n; j++) {
        s << b[i][j];
    }   s << "\n";
    }
    return s;
}

