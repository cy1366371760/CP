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

struct SAT {
    int n, tim, num;
    bool valid;
    vector<vector<int>> adj;
    vector<int> dfn, low, stk, bel;
    vector<bool> ins, hav;
    SAT() {}
    SAT(int n) { // i = sel, i + n = non-sel
        this -> n = n;
        tim = num = 0;
        valid = 1;
        stk.clear();
        adj.assign(2 * n + 5, {});
        dfn.assign(2 * n + 5, 0);
        low.assign(2 * n + 5, 0);
        bel.assign(2 * n + 5, 0);
        ins.assign(2 * n + 5, 0);
        hav.assign(2 * n + 5, 0);
    }
    void dfs(int x) {
        dfn[x] = low[x] = ++tim;
        ins[x] = 1;
        stk.pb(x);
        for (auto v : adj[x]) {
            if (!dfn[v]) {
                dfs(v);
                if (!valid) return;
                low[x] = min(low[x], low[v]);
            } else if (ins[v]) {
                low[x] = min(low[x], dfn[v]);
            }
        }
        if (low[x] == dfn[x]) {
            ++num;
            vector<int> bin;
            while (1) {
                int nw = stk.back();
                stk.pop_back();
                if (nw > n && hav[nw - n] || nw <= n && hav[nw + n]) {
                    valid = false;
                    return;
                }
                hav[nw] = 1, ins[nw] = 0, bel[nw] = num;
                bin.pb(nw);
                if (nw == x) break;
            }
            for (auto v : bin) hav[v] = 0;
            bin.clear();
        }
    }
    void add_edge(int x, int y) {
        adj[x].pb(y);
    }
    pair<bool, vector<int>> sol() {
        valid = 1;
        for (int i = 1; i <= n * 2; i++) {
            if (!dfn[i]) dfs(i);
        }
        vector<int> sel(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            sel[i] = (bel[i] < bel[i + n]);
        }
        return make_pair(valid, sel);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    SAT sat(n);
    for (int i = 1; i <= m; i++) {
        int x, a, y, b;
        cin >> x >> a >> y >> b;
        if (a == 0 && b == 0) {
            sat.add_edge(x, y + n);
            sat.add_edge(y, x + n);
        } else if (a == 0 && b == 1) {
            sat.add_edge(x, y);
            sat.add_edge(y + n, x + n); 
        } else if (a == 1 && b == 0) {
            sat.add_edge(x + n, y + n);
            sat.add_edge(y, x);
        } else { // 1, 1
            sat.add_edge(x + n, y);
            sat.add_edge(y + n, x);
        }
    }
    auto [valid, sel] = sat.sol();
    if (!valid) cout << "IMPOSSIBLE" << nl;
    else {
        cout << "POSSIBLE" << nl;
        for (int i = 1; i <= n; i++) {
            cout << sel[i] << ' ';
        }
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