struct EBCC {
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int tim, cnt;
    
    EBCC() {}
    EBCC(int n) {
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
        adj[v].pb(u);
    }
    
    void dfs(int x, int fa) {
        dfn[x] = low[x] = ++tim;
        stk.pb(x);
        bool skip = 0;
        for (auto y : adj[x]) {
            if (y == fa && !skip) {
                skip = 1;
                continue;
            }
            if (!dfn[y]) {
                dfs(y, x);
                low[x] = min(low[x], low[y]);
            } else {
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
                dfs(i, 0);
            }
        }
        return bel;
    }
    // bel range = [1, cnt]
};