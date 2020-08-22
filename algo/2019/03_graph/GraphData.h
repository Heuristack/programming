#ifndef GRAPH_DATA_H
#define GRAPH_DATA_H

#include <vector>
#include <string>
#include <utility>

using namespace std;

namespace CLRS3
{
    vector<pair<pair<string, string>, double>> const Figure_23_1 = {
        {{"a", "b"}, 4},
        {{"a", "h"}, 8},
        {{"b", "h"},11},
        {{"b", "c"}, 8},
        {{"h", "i"}, 7},
        {{"h", "g"}, 1},
        {{"i", "c"}, 2},
        {{"i", "g"}, 6},
        {{"c", "d"}, 7},
        {{"c", "f"}, 4},
        {{"g", "f"}, 2},
        {{"d", "f"},14},
        {{"d", "e"}, 9},
        {{"e", "f"},10}
    };

    vector<pair<pair<string, string>, double>> const Figure_24_2 = {
        {{"s", "t"}, 3},
        {{"s", "y"}, 5},
        {{"z", "s"}, 3},
        {{"t", "y"}, 2},
        {{"y", "t"}, 1},
        {{"t", "x"}, 6},
        {{"y", "x"}, 4},
        {{"y", "z"}, 6},
        {{"x", "z"}, 2},
        {{"z", "x"}, 7}
    };

    vector<pair<pair<string, string>, double>> const Figure_24_4 = {
        {{"s", "t"}, 6},
        {{"s", "y"}, 7},
        {{"z", "s"}, 2},
        {{"t", "y"}, 8},
        {{"t", "x"}, 5},
        {{"x", "t"},-2},
        {{"t", "z"},-4},
        {{"y", "x"},-3},
        {{"y", "z"}, 9},
        {{"z", "x"}, 7}
    };

    vector<pair<pair<string, string>, double>> const Figure_24_6 = {
        {{"s", "t"},10},
        {{"s", "y"}, 5},
        {{"z", "s"}, 7},
        {{"t", "y"}, 2},
        {{"y", "t"}, 3},
        {{"t", "x"}, 1},
        {{"y", "x"}, 9},
        {{"y", "z"}, 2},
        {{"x", "z"}, 4},
        {{"z", "x"}, 6}
    };
}

namespace TADM2
{
    vector<pair<int,int>> const Figure_5_9 = {
        {1,6},
        {1,2},
        {1,5},
        {2,5},
        {2,3},
        {5,4},
        {3,4}
    };
    auto const & Figure_5_10 = Figure_5_9;
}

#endif

