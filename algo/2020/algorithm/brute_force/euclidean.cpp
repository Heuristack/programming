#include <iostream>
#include "euclidean.ipp"

int main()
{
    std::cout << gcd_recursive(6,9) << std::endl;
    std::cout << gcd_iterative(6,9) << std::endl;
}

