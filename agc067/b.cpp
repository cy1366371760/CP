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

template<class T>
void Add(T &x, T y) {
    x = (x + y) % mod;
}

template<class T>
void Sub(T &x, T y) {
    x = (x - y + mod) % mod;
}

ll qpow(ll x, ll y = mod - 2) {
    ll res = 1;
    while (y) {
        if (y & 1) {
            res = res * x % mod;
        }
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

void solve() {
    int n, m; ll C;
    cin >> n >> m >> C;
    vector mnr(n + 5, vector<int>(n + 5, n + 1));
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        for (int st = l; st >= 1; st--) {
            for (int ii = l; ii <= r; ii++) {
                chkmin(mnr[st][ii], r);
            }
        }
    }
    vector dp(n + 5, vector<ll>(n + 5, 0));
    for (int i = 0; i <= n; i++) {
        dp[i + 1][i] = 1;
    }
    // for (int r = 1; r <= n; r++) {
    //     for (int l = r; l >= 1; l--) {
    //         vector f(n + 5, vector<ll> (n + 5, 0));
    //         f[l - 1][n + 1] = 1;
    //         for (int i = l; i <= r; i++) {
    //             for (int ii = l - 1; ii < i; ii++) {
    //                 for (int jj = i; jj <= n + 1; jj++) {
    //                     ll nw = f[ii][jj] * dp[ii + 1][i - 1] % mod;
    //                     Add(f[i][min(mnr[ii + 1][i], jj)], nw);
    //                     Add(f[i][mnr[ii + 1][i]], nw * (C - 1) % mod);
    //                 }
    //             }
    //         }
    //         dp[l][r] = qpow(C, r - l + 1) % mod;
    //         for (int i = l; i <= r; i++) {
    //             for (int j = r + 1; j <= n + 1; j++) {
    //                 Sub(dp[l][r], f[i][j] * dp[i + 1][r] % mod);
    //             }
    //         }
    //     }
    // }
    for (int l = n; l >= 1; l--) {
        vector f(n + 5, vector<ll> (n + 5, 0));
        f[l - 1][n + 1] = 1;
        for (int i = l; i <= n; i++) {
            for (int ii = l - 1; ii < i; ii++) {
                for (int jj = i; jj <= n + 1; jj++) {
                    ll nw = f[ii][jj] * dp[ii + 1][i - 1] % mod;
                    Add(f[i][min(mnr[ii + 1][i], jj)], nw);
                    Add(f[i][mnr[ii + 1][i]], nw * (C - 1) % mod);
                }
            }
            int r = i;
            dp[l][r] = qpow(C, r - l + 1) % mod;
            for (int i = l; i <= r; i++) {
                for (int j = r + 1; j <= n + 1; j++) {
                    Sub(dp[l][r], f[i][j] * dp[i + 1][r] % mod);
                }
            }
        }
    }
    cout << dp[1][n] << '\n';
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