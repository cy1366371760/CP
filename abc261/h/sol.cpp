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
    int n, m, bg;
    cin >> n >> m >> bg;
    vector adj(n + 5, vector<pll>());
    vector radj(n + 5, vector<pll>());
    vector<int> ind(n + 5, 0);
    vector<int> otd(n + 5, 0);
    vector vis(2, vector<bool> (n + 5, 0));
    vector dp(2, vector<ll>(n + 5));
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        adj[x].eb(y, z);
        radj[y].eb(x, z);
        ++ind[y];
        ++otd[x];
    }
    auto sec_ind = otd;
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    auto upd = [&](auto &&self, int who, int x, ll val) -> void {
        dp[who][x] = val;
        // cerr << who << ' ' << x << ' '<< val << '\n';
        vis[who][x] = 1;
        for (auto [y, d] : radj[x]) {
            if (who == 0) {
                sec_ind[y]--;
                if (!sec_ind[y]) {
                    ll mx = -inf;
                    for (auto [ny, d] : adj[y]) {
                        chkmax(mx, d + dp[0][ny]);
                    }
                    self(self, 1, y, mx);
                }
            } else {
                if (!vis[0][y]) {
                    pq.push(pll(val + d, y));
                }
            }
        }
    };
    for (int i = 1; i <= n; i++) {
        if (!otd[i]) {
            upd(upd, 0, i, 0);
            upd(upd, 1, i, 0);
        }
    }
    while (!pq.empty()) {
        auto [d, x] = pq.top();
        pq.pop();
        if (vis[0][x]) continue;
        upd(upd, 0, x, d);
    }
    if (!vis[0][bg]) cout << "INFINITY  " << '\n';
    else cout << dp[0][bg] << '\n';
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