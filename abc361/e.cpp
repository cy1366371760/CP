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
    cin >> n;
    vector<vector<pii>> adj(n + 5);
    ll tot = 0;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
        tot += w;
    }
    ll ans = 0;
    vector<array<ll, 2>> dp(n + 5);
    auto dfs = [&](auto &&self, int x, int fa) -> void{
        dp[x][0] = dp[x][1] = 0;
        for (auto [y, w] : adj[x]) {
            if (y == fa) continue;
            self(self, y, x);
            chkmax(dp[x][1], dp[y][0] + w);
            if (dp[x][1] > dp[x][0]) swap(dp[x][1], dp[x][0]);
        }
        chkmax(ans, dp[x][0] + dp[x][1]);
    };
    dfs(dfs, 1, 0);
    cout << tot * 2LL - ans << '\n';
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
