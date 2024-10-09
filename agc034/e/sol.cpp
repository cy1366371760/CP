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
#define int long long
using ld = long double;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> imp(n + 1, 0);
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') imp[i + 1] = 1;
    }
    vector adj(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    vector<int> sz;
    vector<pii> cost;
    vector<int> dep(n + 1, 0);
    int cur;
    ll ans = inf;
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        sz[x] = imp[x];
        int sum = 0;
        pii big = pii(-1, -1);
        for (int y : adj[x]) {
            if (y == fa) continue;
            dep[y] = dep[x] + 1;
            self(self, y, x);
            int mn = cost[y].fi + sz[y];
            int mx = cost[y].sc + sz[y];
            if (mn > big.fi) big = pii(mn, mx);
            sum += mx;
            sz[x] += sz[y];
        }
        cost[x].sc = sum;
        int other = sum - big.sc;
        int mn = big.fi;
        if (mn >= other) {
            cost[x].fi = mn - other;
        } else {
            cost[x].fi = (cost[x].sc & 1);
        }
        if (imp[x]) cur += dep[x];
        // cerr << "!!" << x << ' ' << cost[x].fi << ' ' << cost[x].sc << nl;
    };
    for (int rt = 1; rt <= n; rt++) {
        sz.assign(n + 5, 0);
        cost.assign(n + 5, pii(0, 0));
        cur = 0;
        dep[rt] = 0;
        dfs(dfs, rt, 0);
        cur /= 2;
        if (cost[rt].fi == 0) chkmin(ans, cur);
        // if (rt == 2) exit(0);
    }
    if (ans == inf) ans = -1;
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