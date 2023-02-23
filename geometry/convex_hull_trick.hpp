// for min
struct CHT {
    struct line {
        int k,b; line(){}; line(int k,int b): k(k),b(b){}
        double isect(line l){ double db=l.b-b,dk=k-l.k; return db/dk; }
        int operator ()(int x) { return k*x + b; }
    };
    vector<double> x;
    vector<line> ll;
    void init(int k,int b){ x.pb(-1e18),ll.pb({k,b}); }
    void add(int k,int b){
        line l(k,b);
        while(sz(ll)>1&&l.isect(ll[sz(ll)-2])<=x.back()) x.pop_back(),ll.pop_back();
        if(sz(ll)) x.pb(l.isect(ll.back()));
        ll.pb(l);
    }
    int query(int qx){ return ll[upper_bound(all(x),qx)-x.begin()-1](qx); }
};

// for max
struct CHT {
    struct Line {
        mutable int m,b,p;
        bool operator<(const Line& o) const { return m<o.m; }
        bool operator<(int x) const { return p<x; }
    };
    multiset<Line,less<>> st;
    const int inf = 1e18;
    int div(int a,int b) { return (a/b)-((a^b)<0&&a%b); }
    bool isect(multiset<Line>::iterator x,multiset<Line>::iterator y){
        if(y==st.end()) { x->p=inf; return 0; }
        if(x->m==y->m) x->p=x->b>y->b?inf:-inf;
        else x->p=div(y->b-x->b,x->m-y->m);
        return x->p>=y->p;
    }
    void add(int m,int b) {
        auto z=st.insert({m,b,0}),y=z++,x=y;
        while(isect(y,z))z=st.erase(z);
        if(x!=st.begin()&&isect(--x,y))isect(x,y=st.erase(y));
        while((y=x)!=st.begin()&&(--x)->p>=y->p)isect(x,st.erase(y));
    }
    int query(int x){ auto l=*st.lower_bound(x); return (l.m*x)+l.b; }
};