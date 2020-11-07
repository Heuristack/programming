#pragma once

#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <initializer_list>
#include <limits>
#include <variant>
#include <functional>
#include <type_traits>
#include <utility>
#include <cassert>
#include <string>
#include <iostream>
#include <boost/operators.hpp>
#include <boost/tti/has_type.hpp>

namespace { using namespace std;

BOOST_TTI_HAS_TYPE(key_type)

#include "structure/node.hpp"
#include "stream/node.hpp"
#include "structure/edge.hpp"
#include "stream/edge.hpp"
#include "structure/container.hpp"
#include "stream/container.hpp"
#include "data_set/initializers.hpp"

}

