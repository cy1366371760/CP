#include<bits/stdc++.h>

#define ll long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define fi first
#define sc second

#define pii pair<int, int>
#define pll pair<ll, ll>
template<typename T> bool chkmin(T &a, T b){return (b < a) ? a = b, 1 : 0;}
template<typename T> bool chkmax(T &a, T b){return (b > a) ? a = b, 1 : 0;}
using namespace std;
using ld = long double;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

struct DSU {
    DSU() {}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        fa.resize(n + 5);
        iota(all(fa), 0);
        sz.resize(n + 5);
        fill(all(sz), 1);
        sz[0] = 0;
    }
    vector<int> fa;
    vector<int> sz;
    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int merge(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy) return 0;
        if (sz[fx] > sz[fy]) {
            swap(x, y);
            swap(fx, fy);
        }
        fa[fx] = fy;
        sz[fy] += sz[fx];
        return 1;
    }
    int size(int x) {
        return sz[find(x)];
    }
};

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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m + 1), b(m + 1), c(m + 1), d(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];   
    }
    DSU dsu(n);
    while (1) {
        SCC scc(n);
        for (int i = 1; i <= m; i++) {
            while (a[i] <= b[i] && c[i] <= d[i] && dsu.same(a[i], c[i])) {
                ++a[i], ++c[i];
                if (c[i] > d[i]) {
                    cout << "No" << '\n';
                    return;
                }
            }
            if (a[i] <= b[i] && c[i] <= d[i]) {
                scc.add_edge(dsu.find(a[i]), dsu.find(c[i]));
            }
        }
        scc.work();
        if (scc.cnt == n) break;
        vector<int> fir(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            if (!fir[scc.bel[i]]) {
                fir[scc.bel[i]] = i;
            } else {
                dsu.merge(fir[scc.bel[i]], i);
            }
        }
    }
    cout << "Yes" << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}