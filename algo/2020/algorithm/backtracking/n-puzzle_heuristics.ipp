auto hamming(node const & e) -> int
{
    int value = 0;
    for (int i = 0; i < e.n; i++) {
    for (int j = 0; j < e.n; j++) {
        if (e[i][j] != 0 &&
            e[i][j] != goal[i][j]) {
            value++;
        }
    }
    }
    return value;
}

auto manhattan(node const & e) -> int
{
    auto value = 0;
    for (auto i = 0; i < e.n; i++) {
    for (auto j = 0; j < e.n; j++) {
        if (auto g = goal[i][j]; g != 0) {
            auto [p,q] = locate(e,g);
            value += abs(p-i) + abs(q-j);
        }
    }
    }
    return value;
}

typedef int(*heuristic)(node const &);
heuristic nullheuristic = nullptr;

