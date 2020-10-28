#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <initializer_list>
#include <variant>
#include <functional>
#include <iterator>

namespace {

using namespace std;

#include "structure/node.hpp"
#include "stream/node.hpp"

#include "structure/edge.hpp"
#include "stream/edge.hpp"

#include "structure/container.hpp"
#include "stream/container.hpp"

#ifdef IMPLICIT_GRAPH
#include "structure/implicit_graph.hpp"
#else
#include "structure/graph.hpp"
#include "stream/graph.hpp"
#endif

#include "algorithm/search.hpp"

#include "data_set/initializers.hpp"

}

