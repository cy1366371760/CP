struct SCC {
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int tim, cnt;
    
    SCC() {}
    SCC(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        adj.assign(n + 5, {});
        dfn.assign(n + 5, 0);
        low.resize(n + 5);
        bel.assign(n + 5, 0);
        stk.clear();
        tim = cnt = 0;
    }
    
    void add_edge(int u, int v) {
        adj[u].pb(v);
    }
    
    void dfs(int x) {
        dfn[x] = low[x] = ++tim;
        stk.pb(x);
        for (auto y : adj[x]) {
            if (!dfn[y]) {
                dfs(y);
                low[x] = min(low[x], low[y]);
            } else if (!bel[y]) {
                low[x] = min(low[x], dfn[y]);
            }
        }
        
        if (dfn[x] == low[x]) {
            int y;
            ++cnt;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
        }
    }

    vector<int> work() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs(i);
            }
        }
        return bel;
    }
};