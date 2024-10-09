#include<bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(),(x).end()
using namespace std;
const ll inf = 1e18;
#define pll pair<ll, ll>
#define pii pair<int, int>
#define fi first
#define sc second
const int N = 1e6 + 100;

void solve() {
    int n, m;
    cin >> n >> m;
    vector adj(n + 5, vector<int>());
    vector<pii> edges(m + 5);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
        edges[i] = pii(x, y);
    }
    int min_sz = n + 5;
    {
        for (int i = 1; i <= n; i++) {
            vector<int> que;
            vector<int> dep(n + 5, n + 5);
            vector<int> fa(n + 5, 0);
            dep[i] = 0;
            que.pb(i);
            for (int q = 0; q < que.size(); q++) {
                int x = que[q];
                for (int y : adj[x]) {
                    if (dep[y] > dep[x] + 1) {
                        dep[y] = dep[x] + 1;
                        fa[y] = x;
                        que.pb(y);
                    }
                }
            }
            for (auto [x, y] : edges) {
                if (dep[x] == dep[y]) {
                    min_sz = min(min_sz, dep[x] * 2 + 1);
                    continue;
                } 
                if (dep[x] < dep[y]) swap(x, y);
                if (y == fa[x]) continue;
                min_sz = min(min_sz, dep[x] + dep[y] + 1);
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        vector<int> que;
        vector<ll> dp(n + 5, 0);
        vector<int> dep(n + 5, n + 5);
        dp[i] = 1;
        dep[i] = 0;
        que.pb(i);
        for (int q = 0; q < que.size(); q++) {
            int x = que[q];
            for (int y : adj[x]) {
                if (dep[y] > dep[x] + 1) {
                    dep[y] = dep[x] + 1;
                    dp[y] = 0;
                    que.pb(y);
                }
                if (dep[y] == dep[x] + 1) {
                    dp[y] += dp[x];
                }
            }
        }
        if (min_sz % 2 == 0) {
            for (int i = 1; i <= n; i++) {
                if (dep[i] * 2 == min_sz) {
                    ans += dp[i] * (dp[i] - 1) / 2LL;
                }
            }
        } else {
            for (auto [x, y] : edges) {
                if (dep[x] == dep[y] && dep[x] * 2 + 1 == min_sz) {
                    ans += dp[x] * dp[y];
                }
            }
        }
    }
    cout << ans / min_sz << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}