/*
Treap
Description: Stripped down version of Treap
			 Implemented mostly as a set, along with access operator []

Source: It's me. I'm the source. It's me. + KACTL
*/
template<typename T> struct Node {
    Node *l=0,*r=0; T val; int y,c=1;
    Node(T val) : val(val), y(rng()) {}
    void recalc();
};

template<typename T>
int cnt(Node<T>* n) { return n?n->c:0; }
template<typename T>
void Node<T>::recalc() { c=cnt(l)+cnt(r)+1;}

template<typename T> struct Treap {
    using pt=struct Node<T>*;
private:
    pt root=0;
    pair<pt,pt> split(pt n,int k){
        if(!n) return {};
        if(cnt(n->l)>=k){
            auto pa=split(n->l,k); n->l=pa.second; n->recalc();
            return {pa.first,n};
        } else {
            auto pa=split(n->r,k-cnt(n->l)-1); n->r=pa.first; n->recalc();
            return {n,pa.second};
        }
    }
    pt merge(pt l,pt r){
        if(!l) return r;
        if(!r) return l;
        if(l->y > r->y) {
            l->r=merge(l->r,r); l->recalc();
            return l;
        } else {
            r->l=merge(l,r->l); r->recalc();
            return r;
        }
    }
    pt insert(pt t,pt n,int pos){
        auto pa=split(t,pos);
        return merge(merge(pa.first,n),pa.second);
    }
    pt erase(pt n,int l,int r){
        pt a,b,c; tie(a,b)=split(n,l); tie(b,c)=split(b,r-l);
        delete b; b=0;
        return merge(a,c);
    }
    T get(pt n,int idx){
        if(idx<cnt(n->l)) return get(n->l,idx);
        else if(idx>cnt(n->l)) return get(n->r,idx-cnt(n->l)-1);
        return n->val;
    }
public:
    void insert(int pos,T v) { root=insert(root,new Node<T>(v),pos); }
    void push_back(T v) { insert(cnt(root),v); }
    void erase(int l,int r) { root = erase(root, l, r); }
    void erase(int pos) { erase(pos, pos + 1); }
    size_t size() { return cnt(root); }
    int get(int idx) { return get(root,idx); }
    int operator[](int idx) { return get(root,idx); }
    friend ostream& operator << (ostream& os, Treap t) { for(int i=0;i<t.size();i++) cout<<t[i]<<" "; return os; }
};