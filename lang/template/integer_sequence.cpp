#include <cstddef>

template <typename T, T ... Is>
struct integer_sequence
{
    using type = T;
    static constexpr int size()
    {
        return sizeof ... (Is);
    }
};

template <std::size_t ... Is>
using index_sequence = integer_sequence<std::size_t, Is...>;

int main()
{
    using intseq = integer_sequence<int,1,2,3,4,5>;
    static_assert(intseq::size() == 5);
}

