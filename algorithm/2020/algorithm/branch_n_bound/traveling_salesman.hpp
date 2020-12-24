constexpr auto mi = numeric_limits<int>::min();
constexpr auto mx = numeric_limits<int>::max();
constexpr auto n = 6;

vector<vector<int>> cm = {
    {mx,27,43,16,30,26},
    { 7,mx,16, 1,30,25},
    {20,13,mx,35, 5, 0},
    {21,16,25,mx,18,18},
    {12,46,27,48,mx, 5},
    {23, 5, 5, 9, 5,mx},
};

auto show(vector<vector<int>> const & matrix)
{
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (matrix[i][j] == mx) {
            cout << "+*,";
            continue;
        }
        if (matrix[i][j] == mi) {
            cout << "-*,";
            continue;
        }
        cout << setw(2)
        << setfill('0')
        << matrix[i][j]
        << ",";
    }   cout << endl;
    }
}

auto make(vector<vector<int>> const & m)
{
    return vector<vector<int>>(m);
}

auto exclude(vector<vector<int>> & m, int i, int j) -> vector<vector<int>> &
{
    m[i][j] = mx;
    return m;
}

auto include(vector<vector<int>> & m, int i, int j) -> vector<vector<int>> &
{
    for (int k = 0; k < n; k++) {
        m[i][k] = mx;
        m[k][j] = mx;
    }
    return m;
}

auto reduce(vector<vector<int>> & matrix) -> int
{
    int reduced = 0;
    for (int i = 0; i < n; i++) {
        int min = mx;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != mx) {
                matrix[i][j] -= min;
            }
        }
        if (min != mx) {
            reduced += min;
        }
    }
    for (int j = 0; j < n; j++) {
        int min = mx;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] != mx) {
                matrix[i][j] -= min;
            }
        }
        if (min != mx) {
            reduced += min;
        }
    }
    return reduced;
}

auto theta(vector<vector<int>> const & m, int i, int j) -> int
{
    int min, tht = 0;
    min = mx;
    for (int k = 0; k < n; k++) {
        if (k == j) continue;
        if ((m[i][k] != mx) && (m[i][k] < min)) {
            min = m[i][k];
        }
    }
    if (min != mx) {
        tht += min;
    }
    min = mx;
    for (int k = 0; k < n; k++) {
        if (k == i) continue;
        if ((m[k][j] != mx) && (m[k][j] < min)) {
            min = m[k][j];
        }
    }
    if (min != mx) {
        tht += min;
    }
    return tht;
}

auto theta(vector<vector<int>> const & m) -> vector<vector<int>>
{
    vector<vector<int>> t(n,vector<int>(n,0));
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        t[i][j] = theta(m,i,j);
    }
    }
    return t;
}

auto zero(vector<vector<int>> const & m) -> bool
{
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (m[i][j] != 0) {
            return false;
        }
    }
    }
    return true;
}

auto max_element(vector<vector<int>> const & m) -> pair<int,int>
{
    int max = mi;
    int mxi = -1;
    int mxj = -1;
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if ((m[i][j] != mx) && (m[i][j] > max)) {
            max = m[i][j];
            mxi = i;
            mxj = j;
        }
    }
    }
    return {mxi,mxj};
}

auto cans(vector<vector<int>> const & m) -> vector<pair<int,int>>
{
    vector<pair<int,int>> c;
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (m[i][j] != mx) {
            c.emplace_back(i,j);
        }
    }
    }
    return c;
}

