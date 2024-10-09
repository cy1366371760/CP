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
    int n;
    cin >> n;
    vector adj(n + 5, vector<int>());
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    vector<int> dep(n + 5, 0);
    vector<int> mx_d(n + 5, 0);
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        mx_d[x] = dep[x];
        for (int y : adj[x]) {
            if (y == fa) continue;
            dep[y] = dep[x] + 1;
            self(self, y, x);
            chkmax(mx_d[x], mx_d[y]);
        }
    };
    dep[1] = 1;
    dfs(dfs, 1, 0);
    vector sum(2, vector<int>(n + 5, 0));
    for (int i = 1; i <= n; i++) {
        sum[0][dep[i]]++;
        sum[1][mx_d[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        sum[0][i] += sum[0][i - 1];
        sum[1][i] += sum[1][i - 1];
    }
    int ans = n;
    for (int d = 1; d <= n; d++) {
        int cut = sum[0][n] - sum[0][d];
        cut += sum[1][d - 1];
        chkmin(ans, cut);
    }
    cout << ans << nl;
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