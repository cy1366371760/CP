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
const ll mod = 1e9 + 7;

ll qpow(ll x, ll y = mod - 2) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

void solve() {
    int n, d, h;
    cin >> n >> h >> d;
    const int m = 1e6 + 5;
    vector<ll> fac(m + 1, 0);
    fac[0] = 1;
    for (int i = 1; i <= m; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    auto ifac = fac;
    ifac[m] = qpow(fac[m]);
    for (int i = m - 1; i >= 0; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
    vector<ll> dp(h + 5, 0);
    vector<ll> sum(h + 5, 0);
    dp[0] = fac[n]; 
    sum[0] = dp[0];
    ll tmp = 0;
    for (int i = 1; i <= n; i++) {
        tmp = (tmp + fac[i]) % mod;
    }
    for (int i = 1; i <= h; i++) {
        ll nw = sum[i - 1];
        if (i - d > 0) {
            nw = (nw - sum[i - d - 1] + mod) % mod;
        }
        if (i < h) {
            nw = nw * tmp % mod;
        }
        dp[i] = nw;
        sum[i] = (dp[i] + sum[i - 1]) % mod;
    }
    cout << dp[h] << '\n';
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