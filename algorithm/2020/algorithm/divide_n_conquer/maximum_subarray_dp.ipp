int maximum_subarray_dp(vector<int> a)
{
    int min_sum = 0, running_sum = 0, max_sum = 0;
    for (int i = 0; i < a.size(); i++) {
        running_sum += a[i];
        if (running_sum < min_sum) {
            min_sum = running_sum;
        }
        if (running_sum - min_sum > max_sum) {
            max_sum = running_sum - min_sum;
        }
    }
    return max_sum;
}

