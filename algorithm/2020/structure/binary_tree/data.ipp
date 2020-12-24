struct name_data
{
public:
    name_data(char n, long d): name(n),data(d) {}
    name_data(long d): name_data('0',d) {}

public:
    char name;
    long data;
};

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

