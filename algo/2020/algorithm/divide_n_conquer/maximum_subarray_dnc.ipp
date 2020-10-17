template <typename iterator>
auto maximum_subarray(iterator p, iterator m, iterator r)
{
    typename iterator::value_type lower_sum = 0;
    auto lower_max_sum = numeric_limits<typename iterator::value_type>::min();
    iterator lower = m;
    for (auto i = m; i > p; i--) {
        lower_sum += *prev(i);
        if (lower_sum > lower_max_sum) {
            lower_max_sum = lower_sum;
            lower = prev(i);
        }
    }
    typename iterator::value_type upper_sum = 0;
    auto upper_max_sum = numeric_limits<typename iterator::value_type>::min();
    iterator upper = m;
    for (auto i = m; i < r; i++) {
        upper_sum += *i;
        if (upper_sum > upper_max_sum) {
            upper_max_sum = upper_sum;
            upper = i;
        }
    }
    return make_tuple(lower, upper, lower_max_sum + upper_max_sum);
}

template <typename iterator>
auto maximum_subarray(iterator p, iterator r)
{
    auto d = distance(p,r);
    auto m = p + d/2;
    if (d == 1) return make_tuple(p,r,*m);
    auto [mlower,mupper,mmaxsum] = maximum_subarray(p,m,r);
    auto [llower,lupper,lmaxsum] = maximum_subarray(p,m);
    auto [rlower,rupper,rmaxsum] = maximum_subarray(m,r);
    if ((lmaxsum >= rmaxsum) && (lmaxsum >= mmaxsum)) return make_tuple(llower,lupper,lmaxsum);
    if ((rmaxsum >= lmaxsum) && (rmaxsum >= mmaxsum)) return make_tuple(rlower,rupper,rmaxsum);
    return make_tuple(mlower,mupper,mmaxsum);
}

