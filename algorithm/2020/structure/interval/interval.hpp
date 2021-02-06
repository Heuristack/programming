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
    endpoint(int e, int i, int b): e(e),i(i),b(b) {}
    int e,i,b;
};

ostream & operator << (ostream & s, endpoint const & e)
{
    return s << "(" << e.e << "," << e.i << "," << e.b << ")";
}

