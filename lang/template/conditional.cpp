#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

template <bool C, typename T, typename F>
struct Conditional
{
    using type = T;
};

template <typename T, typename F>
struct Conditional<false,T,F>
{
    using type = F;
};

template <bool C, typename T, typename F>
using ConditionalType = typename Conditional<C,T,F>::type;

bool constexpr USE_C_STR = 0;
using String = ConditionalType<USE_C_STR, char *, string>;

int main()
{
    String s {"Hello,World!"};
    static_assert(is_same_v<decltype(s),conditional_t<USE_C_STR,char *,string>> == true);
}

