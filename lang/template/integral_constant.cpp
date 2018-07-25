#include <type_traits>
using namespace std;

int main()
{
    using I1 = integral_constant<int,1>;
    using I2 = integral_constant<int,2>;
    using I3 = integral_constant<int,3>;
    static_assert(I1::value + I2::value == I3::value, "1+2 != 3");
}

