/*
Trie
Description: Trie
			 insert string/sequence
			 and find LCP(longest common prefix) or similar
Source: It's me. I'm the source. It's me.
*/

template<class T> struct Trie {
    struct Node {
        map<T,Node*> nxt;
    };
    Node* root = new Node();
    void insert(vector<T> v){
        Node* cur = root;
        for(auto i : v){
            if(!cur->nxt.count(i)) cur->nxt[i] = new Node();
            cur = cur->nxt[i];
        }
    }
    void inserts(string s) { insert(vector<char>(all(s))); }
    int lcp(vector<T> v){
        Node* cur = root;
        for(int i = 0; i < sz(v); i++){
            if(!cur->nxt.count(v[i])) return i;
            cur = cur->nxt[v[i]];
        }
        return sz(v);
    }
    int lcps(string s){ return lcp(vector<char>(all(s))); }
};