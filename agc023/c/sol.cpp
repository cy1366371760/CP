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
        if (y & 1) {
            res = res * x % mod;
        }
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

ll fac[N], ifac[N];

ll C(ll x, ll y) {
    if (x < y || y < 0) return 0LL;
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}

void solve() {
    ll n;
    cin >> n;
    if (n == 2) {
        cout << 1 << '\n';
        return;
    }
    vector<ll> f(n + 1, 0);
    for (int i = 2; i <= n - 1; i++) {
        // 1 and n - 1 selected, n - 3 remaining
        ll nw = C(i - 1, n - 1 - i);
        f[i] = nw * fac[i] % mod * fac[n - 1 - i] % mod;
        // cerr << i << ' ' << f[i] << '\n';
    }
    vector<ll> g(n + 1, 0);
    ll ans = 0;
    for (int i = 2; i <= n - 1; i++) {
        g[i] = (f[i] - f[i - 1] + mod) % mod;
        ans = (ans + g[i] * i) % mod;
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 1e6 + 3;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    ifac[n] = qpow(fac[n]);
    for (int i = n - 1; i >= 0; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % mod;
    }
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}