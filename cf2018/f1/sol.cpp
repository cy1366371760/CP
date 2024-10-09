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
const int N = 85;
const ll inf = 1e18;

ll dp[N][N][N * 2][N * 2];
bool vis[N][N];

void solve() {
    int n;
    ll _p;
    cin >> n >> _p;
    const ll mod = _p;
    const int bias = n + 1;
    memset(dp, 0, sizeof dp);
    memset(vis, 0, sizeof vis);
    auto Add = [&](ll &x, ll y) {
        x = (x + y) % mod;
    };
    function<void(int, int)> fuck = [&](int len, int mx) -> void {
        if (vis[len][mx]) return;
        vis[len][mx] = 1;
        if (len == 0) {
            for (int l = -n; l <= n; l++) {
                for (int r = l; r <= n; r++) {
                    auto &cur = dp[len][mx][l + bias][r + bias];
                    cur = 1;
                }
            }
            return;
        }
        if (mx > 1) {
            fuck(len, mx - 1);
        } else if (mx == 0) {
            return;
        }
        for (int l = -n; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                auto &cur = dp[len][mx][l + bias][r + bias];
                // non mx
                Add(cur, dp[len][mx - 1][l + bias][r + bias]);
                // first mx
                // [1, len]
                for (int fir = 1; fir <= len; fir++) {
                    if (fir - mx + 1 <= l && fir + mx - 1 >= r && mx >= fir && mx >= len - fir + 1) {
                        fuck(fir - 1, mx - 1);
                        fuck(len - fir, mx);
                        Add(cur, dp[fir - 1][mx - 1][l + bias][r + bias] * dp[len - fir][mx][l - fir + bias][r - fir + bias] % mod);
                    }
                }
            }
        }
    };
    fuck(n, n);
    vector<ll> ans(n + 5, 0);
    for (int l = -n; l <= n; l++) {
        for (int r = max(1, l); r <= n; r++) {
            int tl = max(l, 1);
            int tr = min(r, n);
            Add(ans[tr - tl + 1], dp[n][n][l + bias][r + bias]);
        }
    }
    for (int i = 0; i <= n; i++) {
        cerr << "???" << i << ' ' << ans[i] << nl;
    }
    auto res = ans;
    ll tot = 1;
    for (int i = 1; i <= n; i++) {
        tot = tot * n % mod;
    }
    for (int i = n; i >= 1; i--) {
        if (i == n) {
            res[i] = ans[i];
            continue;
        }
        ll &cur = res[i];
        cur = ans[i];
        for (int j = i + 1; j <= n; j++) {
            cur = (cur - (j - i + 1) % mod * res[j] % mod + mod) % mod;
        }
    }
    res[0] = tot;
    for (int i = 1; i <= n; i++) {
        res[0] = (res[0] - res[i] + mod) % mod;
    }
    for (int i = 0; i <= n; i++) cout << res[i] << ' ';
    cout << nl;
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