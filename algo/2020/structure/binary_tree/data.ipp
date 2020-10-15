template <typename node_type = node<int>>
auto binary_tree_1()
{
    node_type * tree = new node_type(314,
        new node_type(6,
            new node_type(271,
                new node_type(28),
                new node_type(0)),
            new node_type(561,
                nullptr,
                new node_type(3,
                    new node_type(17),
                    nullptr))),
        new node_type(6,
            new node_type(2,
                nullptr,
                new node_type(1,
                    new node_type(401,
                        nullptr,
                        new node_type(641)),
                    new node_type(257))),
            new node_type(271,
                nullptr,
                new node_type(28))));
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

