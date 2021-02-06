struct interval
{
    interval(int p, int q): p(p),q(q) { assert(p < q); }
    int p,q;
};

ostream & operator << (ostream & s, interval const & i)
{
    return s << "(" << i.p << "," << i.q << ")";
}

struct endpoint
{
    endpoint(int e, int i, int m): e(e),i(i),m(m) {}
    int e,i,m;
};

ostream & operator << (ostream & s, endpoint const & e)
{
    return s << "(" << e.e << "," << e.i << "," << e.m << ")";
}

