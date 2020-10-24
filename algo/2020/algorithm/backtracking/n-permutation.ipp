auto generate_permutation(vector<int> s, int n) -> vector<vector<int>>
{
    static vector<vector<int>> permutations;
    static vector<int> path; // note: n-path (track) is n-permutation

    if (!n) {
        permutations.push_back(path);
        return permutations;
    }

    for (auto i = begin(s); i != end(s); i++) {
        path.push_back(*i);
        generate_permutation(remove_copy_it(begin(s),end(s),i),n-1);
        path.pop_back();
    }

    return permutations;
}

