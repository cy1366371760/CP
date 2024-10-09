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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 5);
    vector<int> fr(m + 5, 0);
    vector<int> ed(m + 5, 0);
    vector<int> sta(n + 5, 0);
    vector<int> ufa(n + 5, 0);
    function<int(int)> find = [&](int x){
        return ufa[x] == x ? x : ufa[x] = find(ufa[x]);
    };
    for (int i = 1; i <= n; i++) {
        ufa[i] = i;
    }
    vector<pii> edges;
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        int id = i;
        fr[id] = u;
        ed[id] = v;
        if (c == 1) {
            sta[u] ^= 1;
            sta[v] ^= 1;
            edges.eb(u, v);
        } else {
            int fu = find(u);
            int fv = find(v);
            if (fu != fv) {
                ufa[fu] = fv;
                adj[u].eb(v);
                adj[v].eb(u);
            }
        }
    }
    vector<int> need(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        int rt = find(i);
        if (sta[i] == 1) {
            need[rt] ^= 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (need[i]) {
            cout << "NO" << '\n';
            return;
        }
    }
    cout << "YES" << '\n';
    vector<bool> vis(n + 5, 0);
    auto dfs = [&](auto &&self, int x, int fa) -> void{
        vis[x] = 1;
        for (int y : adj[x]) {
            if (y == fa) {
                continue;
            }
            self(self, y, x);
            sta[x] ^= sta[y];
        }
        if (sta[x] == 1) {
            edges.eb(x, fa);
        }
    };
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(dfs, i, 0);
        }
    }
    {
        vector<vector<pii>> adj(n + 5);
        int id = 0;
        for (auto [x, y] : edges) {
            ++id;
            adj[x].eb(y, id);
            adj[y].eb(x, id);
        }
        vector<bool> vis(id + 5, 0);
        vector<int> ans;
        auto dfs = [&](auto &&self, int x) -> void{
            for (auto [y, id] : adj[x]) {
                if (vis[id]) {
                    continue;
                }
                vis[id] = 1;
                self(self, y);
                ans.eb(y);
            }
        };
        dfs(dfs, 1);
        cout << ans.size() << '\n';
        for (int x : ans) {
            cout << x << ' ';
        }
        cout << ans[0] << ' ';
        cout << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}
