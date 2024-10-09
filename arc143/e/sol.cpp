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
    vector<vector<int>> adj(n + 5);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    string s;
    cin >> s;
    vector<int> sta(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        sta[i] = (s[i - 1] == 'B');
    }
    vector<int> dp(n + 5, 0);
    vector<vector<int>> topo_adj(n + 5);
    vector<int> ind(n + 5, 0);
    auto add_topo_edge = [&](int x, int y) {
        ind[y]++;
        topo_adj[x].pb(y);
    };
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        vector<int> pre, nxt;
        for (int y : adj[x]) {
            if (y == fa) continue;
            self(self, y, x);
            if (dp[y] == 0) {
                pre.pb(y);
            } else nxt.pb(y);
        }
        dp[x] = sta[x];
        for (auto y : pre) {
            add_topo_edge(y, x);
            dp[x] ^= 1;
        }
        for (auto y : nxt) {
            add_topo_edge(x, y);
        }
    };
    dfs(dfs, 1, 0);
    if (dp[1] == 1) {
        cout << -1 << '\n';
        return;
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (!ind[i]) pq.push(i);
    }
    while (pq.size() > 0) {
        int x = pq.top();
        pq.pop();
        cout << x << ' ';
        for (int y : topo_adj[x]) {
            --ind[y];
            if (!ind[y]) {
                pq.push(y);
            }
        }
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