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

void solve() {
    int n, m;
    cin >> n >> m;
    BCC bcc(n);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        bcc.add_edge(x, y);
    }
    auto bccs = bcc.work();
    cout << bccs.size() << nl;
    for (auto bcc : bccs) {
        cout << bcc.size() << ' ' ;
        for (int x : bcc) cout << x << ' ';
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