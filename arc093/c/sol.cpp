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
const ll mod = 1e9 + 7;

ll qpow(ll x, ll y = mod - 2) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

void solve() {
    int n, m;
    ll X;
    cin >> n >> m >> X;
    vector<array<ll, 3>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }
    sort(all(edges), [](auto u, auto v) {
        return u[2] < v[2];
    });
    vector<bool> sel(m + 5, 0);
    vector<int> ufa(n + 1, 0);
    iota(all(ufa), 0);
    auto find = [&](auto &&self, int x) -> int {
        return ufa[x] == x ? x : ufa[x] = self(self, ufa[x]);
    };  
    vector adj(n + 1, vector<pll>());
    ll sum = 0;
    for (int i = 0; i < m; i++) {
        auto [u, v, w] = edges[i];
        int fu = find(find, u);
        int fv = find(find, v);
        if (fu == fv) continue;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
        sum += w;
        ufa[fu] = fv;
        sel[i] = 1;
    }
    if (X < sum) {
        cout << 0 << '\n';
        return;
    }
    vector jp(21, vector<int>(n + 1, 0));
    vector mx(21, vector<ll> (n + 1, 0));
    vector<int> dep(n + 1, 0);
    auto dfs = [&](auto &&self, int x, int fa, ll tofa) -> void {
        jp[0][x] = fa;
        mx[0][x] = tofa;
        for (int j = 1; j <= 20; j++) {
            jp[j][x] = jp[j - 1][jp[j - 1][x]];
            mx[j][x] = max(mx[j - 1][x], mx[j - 1][jp[j - 1][x]]);
        }
        for (auto [y, z] : adj[x]) {
            if (y == fa) continue;
            dep[y] = dep[x] + 1;
            self(self, y, x, z);
        }
    };
    dep[1] = 1;
    dfs(dfs, 1, 0, 0);
    map<ll, int> gain;
    auto cal_lca = [&](int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        int d = dep[x] - dep[y];
        for (int i = 20; i >= 0; i--) {
            if (d >> i & 1) x = jp[i][x];
        }
        if (x == y) return x;
        for (int i = 20; i >= 0; i--) {
            if (jp[i][x] != jp[i][y]) {
                x = jp[i][x];
                y = jp[i][y];
            }
        }
        return jp[0][x];
    };
    auto ask_max = [&](int x, int y) {
        int d = dep[x] - dep[y];
        ll res = 0;
        for (int j = 20; j >= 0; j--) {
            if (d >> j & 1) {
                chkmax(res, mx[j][x]);
                x = jp[j][x];
            }
        }
        return res;
    };
    for (int i = 0; i < m; i++) {
        auto [u, v, w] = edges[i];
        if (sel[i]) continue;
        auto lca = cal_lca(u, v);
        ll ex = w - max(ask_max(u, lca), ask_max(v, lca));
        gain[ex]++;
    }
    if (X == sum) {
        ll ans = 0;
        int maybe = n - 1 + gain[0];
        ans = (ans + (qpow(2, maybe) - 2 + mod) % mod * qpow(2, m - maybe) % mod) % mod;
        cout << ans << '\n';
        return;
    }
    int small = n - 1;
    int exact = 0;
    int big = 0;
    ll need = X - sum;
    for (auto [ex, cnt] : gain) {
        if (ex < need) small += cnt;
        if (ex == need) exact += cnt;
        if (ex > need) big += cnt; 
    }
    ll ans = 2LL * (qpow(2, exact) - 1 + mod) % mod * qpow(2, big) % mod;
    cout << ans << '\n';
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