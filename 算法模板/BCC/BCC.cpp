struct BCC {
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low;
    vector<vector<int>> bccs;
    int tim, cnt;
    
    BCC() {}
    BCC(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        adj.assign(n + 5, {});
        dfn.assign(n + 5, 0);
        low.resize(n + 5);
        bccs.clear();
        stk.clear();
        tim = cnt = 0;
    }
    
    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    void dfs(int x) {
        dfn[x] = low[x] = ++tim;
        stk.pb(x);
        for (auto y : adj[x]) {
            if (!dfn[y]) {
                dfs(y);
                low[x] = min(low[x], low[y]);
                if (low[y] >= dfn[x]) {
                    vector<int> bcc;
                    int del;
                    do {
                        del = stk.back();
                        stk.pop_back();
                        bcc.pb(del);
                    } while (del != y);
                    bcc.pb(x);
                    bccs.pb(bcc);
                }
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
    }

    vector<vector<int>> work() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs(i);
                if (tim == dfn[i]) { // alone
                    bccs.pb({i});
                }
            }
        }
        return bccs;
    }
};