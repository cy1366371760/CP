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
const ll mod = 1e9 + 7;

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}

void solve() {
    int n;
    cin >> n;
    vector adj(n + 5, vector<int>());
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    vector<ll> pw2(n + 5, 0);
    pw2[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw2[i] = pw2[i - 1] * 2 % mod;
    }
    vector<int> dep(n + 5, 0);
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        for (int y : adj[x]) {
            if (y == fa) continue;
            dep[y] = dep[x] + 1;
            self(self, y, x);
        }
    };
    int D;
    vector<int> ed(2, -1);
    vector hav(2, vector(n + 5, vector<int>()));
    dep[1] = 0;
    dfs(dfs, 1, 0);
    ed[0] = 1;
    for (int i = 2; i <= n; i++) {
        if (dep[i] > dep[ed[0]]) {
            ed[0] = i;
        }
    }
    dep[ed[0]] = 0;
    dfs(dfs, ed[0], 0);
    ed[1] = 1;
    for (int i = 1; i <= n; i++) {
        hav[0][dep[i]].pb(i);
        if (dep[i] > dep[ed[1]]) {
            ed[1] = i;
        }
    }
    D = dep[ed[1]];
    // cerr << ed[0] << ' ' << ed[1] << ' ' << D << nl;
    dep[ed[1]] = 0;
    dfs(dfs, ed[1], 0);
    for (int i = 1; i <= n; i++) {
        hav[1][dep[i]].pb(i);
    }
    int las = n;
    ll ans = 0;
    vector<int> vis(n + 5, 0);
    for (int del = D; ; del--) {
        ll nw = del;
        bool gg = 0;
        for (int x : hav[0][del]) {
            if (vis[x]) {
                gg = 1;
            }
            vis[x] = 1;
        }
        for (int x : hav[1][del]) {
            if (vis[x]) {
                gg = 1;
            }
            vis[x] = 1;
        }
        if (gg) {
            Add(ans, (del == D ? 1LL : 2LL) * pw2[las] * nw % mod); 
            break;
        }
        int cnt = hav[0][del].size() + hav[1][del].size();
        ll cur = (del == D ? pw2[cnt] - 2 + mod : pw2[cnt] - 1 + mod) % mod;
        cur = cur * nw % mod * (del == D ? 1LL : 2LL) % mod * pw2[las - cnt] % mod;
        Add(ans, cur);
        las -= cnt;
        // cerr << "!!" << del << ' ' << cur << nl;
    }
    cout << ans << nl;
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