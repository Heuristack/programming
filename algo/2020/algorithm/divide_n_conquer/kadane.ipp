auto kadane(vector<int> a) {
    int max_ending = 0;
    int max_slice = 0;
    for (auto const & e : a) {
//      cout << e << ":(" << max_ending << "," << max_slice << ")";
//      cout << "->";
        max_ending = max(0,max_ending+e);
        max_slice = max(max_slice, max_ending);
//      cout << "(" << max_ending << "," << max_slice << ")";
//      cout << endl;
    }
    return max_slice;
}

