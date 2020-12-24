#include <iostream>
#include <cassert>
#include <vector>
#include <set>

#include "union_find.hpp"

template <typename element_t> using normalized_map = std::vector<element_t>;

int main()
{
    union_find<int,normalized_map> u(10);
    u(4,3)(3,8)(6,5)(9,4)(2,1)(8,9)(5,0)(7,2)(6,1)(1,0)(6,7);
    std::cout << u.count() << std::endl;
}
// Sedgewick, R. and Wayne, K., 2011. Algorithms. Addison-wesley professional. Section 1.5, pp.220

