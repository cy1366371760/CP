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

void solve() {
    int n;
    int m = 1e5;
    cin >> n;
    vector<int> a(n + 5);
    vector<vector<int>> hav(m + 5);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        for (int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j == 0) {
                hav[j].pb(i);
                if (j * j != a[i]) {
                    hav[a[i] / j].pb(i);
                }
            }
        }
    }
    vector<vector<int>> adj(n + 5);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    ll res;
    vector<ll> ans(m + 5);
    vector<bool> valid(m + 5, 0);
    vector<ll> dep(n + 5), sum_dep(n + 5), sz(n + 5);
    auto dfs = [&](auto &&self, int x) -> void {
        valid[x] = 0;
        sz[x] = 1;
        sum_dep[x] = dep[x];
        for (auto y : adj[x]) {
            if (valid[y]) {
                dep[y] = dep[x] + 1;
                self(self, y);
                res += ((sum_dep[y] - dep[x] * sz[y]) % mod * sz[x] + (sum_dep[x] - (dep[x] - 1) * sz[x]) % mod * sz[y]) % mod;
                sum_dep[x] += sum_dep[y];
                sz[x] += sz[y];
            }
        }
    };
    for (int v = 1; v <= m; v++) {
        for (auto x : hav[v]) {
            valid[x] = 1;
        }
        res = 0;
        for (auto x : hav[v]) {
            if (!valid[x]) continue;
            dep[x] = 1, dfs(dfs, x);
        }
        ans[v] = res;
    }
    res = 0;
    for (int v = m; v >= 1; v--) {
        for (int big = v * 2; big <= m; big += v) {
            ans[v] = (ans[v] - ans[big] + mod) % mod;
        }
        // if (ans[v]) cerr << "!!" << v << ' ' << ans[v] << '\n';
        res = (res + ans[v] * v) % mod;
    }
    cout << res << '\n';
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