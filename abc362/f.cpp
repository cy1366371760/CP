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
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int rt = -1, best = n + 5;
    vector<int> sz(n + 5, 0);
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        int nw = 0;
        sz[x] = 1;
        for (auto y : adj[x]) {
            if (y == fa) continue;
            self(self, y, x);
            sz[x] += sz[y];
            nw = max(nw, sz[y]);
        }
        nw = max(nw, n - sz[x]);
        if (nw < best) {
            best = nw;
            rt = x;
        }
    };
    dfs(dfs, 1, 0);
    int idx = 0;
    vector<vector<int>> hav(n + 5);
    vector<int> cnt(n + 5, 0);
    auto dfs2 = [&](auto &&self, int x, int fa) -> void {
        hav[idx].pb(x);
        cnt[idx]++;
        for (auto y : adj[x]) {
            if (y == fa) continue;
            if (fa == 0) {
                idx++;
            }
            self(self, y, x);
        }
    };
    dfs2(dfs2, rt, 0);
    priority_queue<pii> pq;
    for (int i = 0; i <= idx; i++) {
        pq.push({cnt[i], i});
    }
    for (int i = 1; i <= n / 2; i++) {
        auto [sz1, id1] = pq.top();
        pq.pop();
        auto [sz2, id2] = pq.top();
        pq.pop();
        cout << hav[id1].back() << ' ' << hav[id2].back() << '\n';
        hav[id1].pop_back();
        hav[id2].pop_back();
        if (sz1 - 1) pq.push({sz1 - 1, id1});
        if (sz2 - 1) pq.push({sz2 - 1, id2});
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
