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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pii> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].fi >> a[i].sc;
        if (a[i].fi > a[i].sc) {
            swap(a[i].fi, a[i].sc);
        }
    }
    sort(all(a));
    a.erase(unique(all(a)), a.end());
    m *= 2;
    vector adj(m + 1, vector<int>());
    for (auto [x, y] : a) {
        if (x == y) adj[x].pb(x + m / 2), adj[x + m / 2].pb(x);
        else {
            adj[x].pb(y);
            adj[y].pb(x);
        }
    }
    priority_queue<pii> pq;
    for (int i = 1; i <= m; i++) {
        if (adj[i].size()) {
            pq.push({adj[i].size(), i});
        }
    }
    vector<bool> vis(m + 5, 0);
    auto dfs = [&](auto &&self, int x, int fa) -> int {
        //  cerr << "dd" << ' ' << x << nl;
        vis[x] = 1;
        for (int y : adj[x]) {
            if (y == x) continue;
            if (vis[y]) continue;
            if (adj[y].size() == 1) {
                vis[y] = 1;
            }
        }
        vector<int> remain;
        vector<int> bf;
        for (int y : adj[x]) {
            if (y == x) {
                continue;
            }
            if (adj[y].size() > 1) {
                if (vis[y]) {
                    if (y == fa) continue;
                    bf.pb(y);
                } else {
                    remain.pb(y);
                }
            }
        }
        if (bf.size() > 1 || remain.size() > 1 || (remain.size() && bf.size())) {
            cout << "impossible" << nl;
            exit(0);
        }
        int res = 0;
        if (remain.size()) {
            res = self(self, remain[0], x);
        } else {
            if (bf.size()) res = bf[0];
        }
        return res;
    };
    int loop = 0;
    int nloop = 0;
    auto doit = [&](int x) -> void {
        // cerr << "GG" << x << nl;
        vis[x] = 1;
        for (int y : adj[x]) {
            if (y == x) continue;
            if (adj[y].size() == 1) {
                vis[y] = 1;
            }
        }
        vector<int> remain;
        for (int y : adj[x]) {
            if (y == x) continue;
            if (adj[y].size() > 1) {
                remain.pb(y);
            }
        }
        // cerr << "fuck" << nl;
        // for (int x : remain) cerr << x << ' '; cerr << nl;
        if (remain.size() >= 3) {
            cout << "impossible" << nl;
            exit(0);
        }
        if (remain.size() == 1) {
            int to = remain[0];
            int bad = dfs(dfs, to, x);
            // cerr << to << ' ' << bad << nl;
            if (bad) {
                if (bad == x) {
                    loop += 1;
                    return;
                } else {
                    cout << "impossible" << nl;
                    exit(0);
                }
            }
            nloop += 1;
        } else if (remain.size() == 2) {
            int to1 = remain[0];
            int to2 = remain[1];
            int bad = dfs(dfs, to1, x);
            if (bad) {
                if (bad == x && vis[to2]) {
                    loop += 1;
                    return;
                } else {
                    cout << "impossible" << nl;
                    exit(0);
                }
            }
            bad = dfs(dfs, to2, x);
            if (bad) {
                cout << "impossible" << nl;
                exit(0);
            } 
            nloop += 1;
        } else {
            nloop += 1;
        }
    };
    while (!pq.empty()) {
        auto [_, x] = pq.top();
        pq.pop();
        if (vis[x]) continue;
        // cerr << "!!" << ' ' << x << nl;;
        doit(x);
    }
    // cerr << loop << ' ' << nloop << nl;
    if ((loop == 1 && !nloop) || !loop) {
        cout << "possible" << nl;
    } else {
        cout << "impossible" << nl;
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