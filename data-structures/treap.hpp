/*
Treap
Description: Randomized BBST,
			 use it similar to Segment Tree(given code finds the sum in range),
			 functions supported:
			 find sum of range
			 insert at some position
			 point/range updates (lazy)
			 erase point/range
			 reverse range
			 other operations can be done by split/merge
Time: O(log n) [ Although non-deterministic/random ]
Source: Mostly mine + KACTL
*/

template<typename T>
struct Node {
    Node *l = 0, *r = 0;
    T val, add = 0, sum;
    int y, c = 1, rev = 0;
    Node(T val) : val(val), sum(val), y(rng()) {}
    void recalc();
};

template<typename T>
int cnt(Node<T>* n) { return n ? n->c : 0; }
template<typename T>
void Node<T>::recalc() { c = cnt(l) + cnt(r) + 1, sum = val + (l ? l->sum : 0) + (r ? r->sum : 0); }

template<typename T>
struct Treap {
    using pt = struct Node<T>*;
private:
    pt root = 0;
    template<class F> void each(pt n, F f) {
        push(n);
        if (n) { each(n->l, f); f(n->val); each(n->r, f); }
    }
    void upd(pt n, T add,int rev){
        if(!n) return;
        n->add += add, n->rev ^= rev, n->val += add, n->sum += (cnt(n) * add);
    }
    void push(pt n){
        if(!n || (n->add == 0 && n->rev == 0)) return;
        upd(n->l, n->add, n->rev);
        upd(n->r, n->add, n->rev);
        if(n->rev) swap(n->l, n->r);
        n->add = 0, n->rev = 0;
    }
    pair<pt, pt> split(pt n, int k) {
        if (!n) return {};
        push(n);
        if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
            auto pa = split(n->l, k);
            n->l = pa.second;
            n->recalc();
            return {pa.first, n};
        } else {
            auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
            n->r = pa.first;
            n->recalc();
            return {n, pa.second};
        }
    }
    pt merge(pt l, pt r) {
        push(l);
        push(r);
        if (!l) return r;
        if (!r) return l;
        if (l->y > r->y) {
            l->r = merge(l->r, r);
            l->recalc();
            return l;
        } else {
            r->l = merge(l, r->l);
            r->recalc();
            return r;
        }
    }
    pt ins(pt t, pt n, int pos) {
        push(t);
        auto pa = split(t, pos);
        return merge(merge(pa.first, n), pa.second);
    }
    // Example application: move the range [l, r) to index k
    void move(pt& t, int l, int r, int k) {
        pt a, b, c;
        tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
        if (k <= l) t = merge(ins(a, b, k), c);
        else t = merge(a, ins(c, b, k - r));
    }
    pt reverse(pt n,int l,int r){
        pt a, b, c;
        tie(a,b) = split(n, l); tie(b,c) = split(b, r - l);
        upd(b, 0, 1);
        return merge(merge(a,b), c);
    }
    T sum(Node<T>* n,int l,int r){
        pt a, b, c;
        tie(a,b) = split(n, l); tie(b,c) = split(b, r - l);
        T sm = b->sum;
        root = merge(merge(a,b), c);
        return sm;
    }
    pt add(pt n,int l,int r,int delta){
        pt a, b, c;
        tie(a,b) = split(n, l); tie(b,c) = split(b, r - l);
        upd(b, delta, 0);
        return merge(merge(a,b), c);
    }
    pt erase(pt n, int l,int r) {
        pt a, b, c;
        tie(a,b) = split(n, l); tie(b,c) = split(b, r - l);
        delete b;
        b = 0;
        return merge(a,c);
    }
public:
    void ins(int pos, T v) { root = ins(root, new Node<T>(v), pos); }
    void push_back(T v) { ins(cnt(root), v); }
    void move(int l, int r, int k) { move(root, l, r, k); }
    void reverse(int l,int r){ root = reverse(root, l, r); }
    T sum(int l,int r) { return sum(root, l, r); }
    void add(int l,int r,int delta){ root = add(root, l, r, delta); }
    void erase(int l,int r) { root = erase(root, l, r); }
    void erase(int pos) { erase(pos, pos + 1); }
    size_t size() { return cnt(root); }
    void print(){ each(root,[](T x){ cout << x <<' '; });}
};