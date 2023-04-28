/*
Tree (undirected, unweighted acyclic graph)
Description: 1. Dfs.
             2. Find the centroid(s).
             3. Find the hash of the tree(based on paranthesizing)
Source: Mine
*/

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sub,centroids;
    vector<mint> pw,id;

    Tree(int n): n(n) {
        g.resize(n),sub.assign(n,0),pw.assign(2*n+10,1),id.resize(n);
        for(int i=1;i<(int)pw.size();i++){ pw[i]=pw[i-1]*2; }
    }

    void add_edge(int u,int v) { g[u].push_back(v), g[v].push_back(u); }

    void dfs(int u,int p=-1){
        sub[u]=1,id[u]=1;
        bool is_centroid=1;
        vector<pair<int,int>> kinder;
        for(int i:g[u]){
            if(i==p)continue;
            dfs(i,u);
            sub[u]+=sub[i];
            is_centroid&=(sub[i]<=(n/2));
            kinder.emplace_back(id[i],i);
        }
        sort(kinder.begin(),kinder.end());
        for(auto [x,y]:kinder) {
            id[u]*=pw[sub[y]*2];
            id[u]+=x;
        }
        id[u]*=2;
        is_centroid&=((n-sub[u])<=(n/2));
        if(is_centroid) centroids.push_back(u);
    }

    vector<int> centroid(){ centroids.clear(); dfs(0); return centroids; }

    mint hash(int u){ dfs(u); return id[u]; }
};