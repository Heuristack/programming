struct name_data
{
public:
    name_data(char n, long d): name(n),data(d) {}
    name_data(long d): name_data('0',d) {}

public:
    char name;
    long data;
};

bool operator < (name_data const & a, name_data const & b) { return a.data < b.data; }
bool operator > (name_data const & a, name_data const & b) { return a.data > b.data; }

ostream & operator << (ostream & s, name_data const & v)
{
    return s << v.name << ":" << v.data;
}

template <typename node_type = node<name_data>>
auto binary_tree_1()
{
    node_type * tree = new node_type({'A',314},
        new node_type({'B',6},
            new node_type({'C',271},
                new node_type({'D',28}),
                new node_type({'E',0})),
            new node_type({'F',561},
                nullptr,
                new node_type({'G',3},
                    new node_type({'H',17}),
                    nullptr))),
        new node_type({'I',6},
            new node_type({'J',2},
                nullptr,
                new node_type({'K',1},
                    new node_type({'L',401},
                        nullptr,
                        new node_type({'M',641})),
                    new node_type({'N',257}))),
            new node_type({'O',271},
                nullptr,
                new node_type({'P',28}))));
    return tree;
}

template <typename node_type = node<char>>
auto binary_tree_2()
{
    node_type * tree = new node_type('A',
        new node_type('B',
            new node_type('C',
                new node_type('D',
                    new node_type('E'),
                    new node_type('F')),
                new node_type('G')),
            new node_type('H',
                new node_type('I'),
                new node_type('J'))),
        new node_type('K',
            new node_type('L',
                new node_type('M'),
                new node_type('N')),
            new node_type('O')));
    return tree;
}

template <typename node_type = node<int>>
auto binary_tree_3()
{
    node_type * tree = new node_type(19,
        new node_type(7,
            new node_type(3,
                new node_type(2),
                new node_type(5)),
            new node_type(11,
                nullptr,
                new node_type(17,
                    new node_type(13),
                    new node_type(20)))), // breaks BST property
        new node_type(43,
            new node_type(23,
                nullptr,
                new node_type(37,
                    new node_type(29,
                        nullptr,
                        new node_type(31)),
                    new node_type(41))),
            new node_type(47,
                nullptr,
                new node_type(53))));
    return tree;
}

template <typename node_type = node<name_data>>
auto binary_tree_4()
{
    node_type * tree = new node_type({'A',19},
        new node_type({'B',7},
            new node_type({'C',3},
                new node_type({'D',2}),
                new node_type({'E',5})),
            new node_type({'F',11},
                nullptr,
                new node_type({'G',17},
                    new node_type({'H',13}),
                    nullptr))),
        new node_type({'I',43},
            new node_type({'J',23},
                nullptr,
                new node_type({'K',37},
                    new node_type({'L',29},
                        nullptr,
                        new node_type({'M',31})),
                    new node_type({'N',41}))),
            new node_type({'O',47},
                nullptr,
                new node_type({'P',53}))));
    return tree;
}

template <typename node_type = node<name_data>>
auto binary_tree_5()
{
    node_type * tree = new node_type({'A',108},
        new node_type({'B',108},
            new node_type({'L',-10},
                new node_type({'D',-14}),
                new node_type({'E',2})),
            new node_type({'F',108})),
        new node_type({'G',285},
            new node_type({'H',243}),
            new node_type({'I',285},
                nullptr,
                new node_type({'J',401}))));
    return tree;
}

