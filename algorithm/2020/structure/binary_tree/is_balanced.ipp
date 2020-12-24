template<typename node_t>
auto is_balanced(node_t * tree)
{
// note : return -1 if tree is unblanced else height
    if (!tree) return 0;
    auto l = is_balanced<node_t>(tree->ltree);
    auto r = is_balanced<node_t>(tree->rtree);
//  cout << (*tree) << ":" << l << "," << r << endl;
    if (l < 0 || r < 0 || abs(l-r) > 1) return -1;
    else return max(l,r) + 1;
}

