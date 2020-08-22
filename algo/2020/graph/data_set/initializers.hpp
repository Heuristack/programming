static initializer_list<edge<string,int>> clrs2301 = {
    {"A","B", 4}, {"A","H", 8},
    {"B","H",11}, {"B","C", 8},
    {"H","I", 7}, {"H","G", 1},
    {"I","C", 2}, {"I","G", 6},
    {"C","D", 7}, {"C","F", 4},
    {"G","F", 2},
    {"D","F",14}, {"D","E", 9},
    {"E","F",10},
};

static initializer_list<edge<string,int>> clrs2402 = {
    {"S", "T", 3}, {"S", "Y", 5},
    {"T", "Y", 2}, {"T", "X", 6},
    {"X", "Z", 2},
    {"Y", "T", 1}, {"Y", "X", 4}, {"Y", "Z", 6},
    {"Z", "X", 7}, {"Z", "S", 3},
};

static initializer_list<edge<string,int>> clrs2404 = {
    {"S", "T", 6}, {"S", "Y", 7},
    {"T", "Z",-4}, {"T", "Y", 8}, {"T", "X", 5},
    {"X", "T",-2},
    {"Y", "X",-3}, {"Y", "Z", 9},
    {"Z", "S", 2}, {"Z", "X", 7},
};

static initializer_list<edge<string,int>> clrs2406 = {
    {"S", "T",10}, {"S", "Y", 5},
    {"T", "Y", 2}, {"T", "X", 1},
    {"X", "Z", 4},
    {"Y", "T", 3}, {"Y", "X", 9}, {"Y", "Z", 2},
    {"Z", "S", 7}, {"Z", "X", 6},
};

static initializer_list<edge<int>> manual0509 = {
    {1,6}, {1,2}, {1,5},
    {2,5}, {2,3},
    {5,4},
    {3,4},
};

static initializer_list<variant<node<int>,edge<int>>> varis = {
    variant<node<int>,edge<int>>{in_place_index_t<1>{},1,2},
    edge<int>{2,3},
    {4},
//  {5,6}
};

