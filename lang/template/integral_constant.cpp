#include <type_traits>

template <typename T, T v>
struct integral_constant
{
    using value_type = T;
    static constexpr value_type value = v;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

int main()
{
    using I0 = integral_constant<int,0>;
    static_assert(std::is_same<I0::value_type, int>::value, "expect: value_type = int");
    static_assert(I0::value == 0, "expect: value = 0");
    static_assert(std::is_same<I0::type, I0>::value, "expect: type = integral_constant<int,0>");
    static_assert(static_cast<int>(I0{}) == 0, "expect: cast<int>(I0{}) = 0");
    static_assert(I0{}() == 0, "expect: I0{}() = 0");

    using I1 = integral_constant<int,1>;
    using I2 = integral_constant<int,2>;
    using I3 = integral_constant<int,3>;
    static_assert(I1::value + I2::value == I3::value, "1+2 != 3");
}

