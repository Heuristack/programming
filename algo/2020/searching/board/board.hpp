template <typename element, typename vector_base = vector<element>, typename board_base = vector<vector_base>>
class board : public board_base
{
public:
    using board_base::board_base;
    board(int m, int n) : board_base(m,vector_base(n)) {}
    explicit board(int n) : board(n,n) {}

public:
    int size_m([[maybe_unused]] int i = 0) const { return this->size(); }
    int size_n(int i = 0) const { return this->operator[](i).size(); }
};

template <typename element>
auto operator << (ostream & s, board<element> const & b) -> ostream &
{
    for (int i = 0; i < b.size_m(i); i++) {
    for (int j = 0; j < b.size_n(i); j++) {
        s << b[i][j];
    }   s << "\n";
    }
    return s;
}
