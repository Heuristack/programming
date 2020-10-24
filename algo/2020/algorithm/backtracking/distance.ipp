auto hamming(node const & a, node const & b) -> int
{
    int n = min(a.n,b.n);
    int distance = 0;
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (a[i][j] == 0 || b[i][j] == 0) continue;
        if (a[i][j] != b[i][j]) {
            distance++;
        }
    }
    }
    return distance;
}

auto manhattan(node const & a, node const & b) -> int
{
    int n = min(a.n,b.n);
    int distance = 0;
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (a[i][j] == 0 || b[i][j] == 0) continue;
        auto [p,q] = locate(a,b[i][j]);
        distance += abs(p-i) + abs(q-j);
    }
    }
    return distance;
}

