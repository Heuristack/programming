struct interval
{
    interval(int p, int q, int op, int oq): p(p),q(q),op(op),oq(oq) {}
    interval(int p, int q): interval(p,q,0,0) {}
    int p,q,op,oq;
};

ostream & operator << (ostream & s, interval const & i)
{
    if (!i.op) s << "["; else s << "(";
    s << i.p << "," << i.q;
    if (!i.oq) s << "]"; else s << ")";
    return s;
}

struct endpoint
{
    endpoint(int e, int i, int m, int o): e(e),i(i),m(m),o(o) {}
    endpoint(int e, int i, int m): endpoint(e,i,m,0) {}
    int e,i,m,o; // m - begin(0),end(1); o - open(1),close(0);
};

ostream & operator << (ostream & s, endpoint const & e)
{
    return s << "(" << e.e << "," << e.i << "," << e.m << ")";
}

