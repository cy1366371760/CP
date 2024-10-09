#include<bits/stdc++.h>

#define nl '\n'
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

void solve() {
    int n, m;
    cin >> n >> m;
    ECC ecc(n);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        ecc.add_edge(x, y);
    }
    auto bel = ecc.work();
    vector hav(ecc.cnt + 5, vector<int>());
    for (int i = 1; i <= n; i++) {
        hav[bel[i]].pb(i);
    }
    cout << ecc.cnt << nl;
    for (int i = 1; i <= ecc.cnt; i++) {
        cout << hav[i].size() << ' ';
        for (auto x : hav[i]) cout << x << ' ';
        cout << nl;
    }
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