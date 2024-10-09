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
    ll a[3];
    // ll test = 0;
    // for (int i = 10; i <= 99; i++) {
    //     for (int j = 100; j <= 999; j++) {
    //         if (i + j > 999) test++;
    //     }
    // }
    // cerr << test << '\n';
    cin >> a[0] >> a[1] >> a[2];
    if (a[0] > a[1]) swap(a[0], a[1]);
    if (a[2] == a[1]) {
        if (a[0] == a[1]) {
            ll tmp = 8LL * qpow(10, a[0] - 1) % mod;
            ll res = (1LL + tmp) * tmp % mod * qpow(2) % mod;
            cout << res << '\n';
        } else {
            ll high = a[1] - a[0];
            ll c1 = 9LL * qpow(10, high - 1) % mod;
            c1 = (c1 - 1 + mod) % mod;
            ll res = c1 * 9LL % mod * qpow(10, a[0] - 1) % mod * qpow(10, a[0]) % mod;
            // cerr << "??" << res << '\n';
            {
                ll k = a[0];
                ll tmp = 9LL * qpow(10, a[0] - 1) % mod;
                res = (res + (1LL + tmp) * tmp % mod * qpow(2) % mod) % mod;
            }
            cout << res << '\n';
        }
    } else if (a[2] == a[1] + 1) {
        if (a[0] == a[1]) {
            ll k = a[0];
            ll tmp = 8LL * qpow(10, a[0] - 1) % mod;
            ll res = (1LL + tmp) * tmp % mod * qpow(2) % mod;
            ll tot = 9LL * qpow(10, a[0] - 1) % mod * 9LL % mod * qpow(10, a[0] - 1) % mod;
            res = (tot - res + mod) % mod;
            cout << res << '\n';
        } else {
            ll k = a[0];
            ll tmp = 9LL * qpow(10, a[0] - 1) % mod;
            ll res = (1LL + tmp) * tmp % mod * qpow(2) % mod;
            ll tot = 10LL * qpow(10, a[0] - 1) % mod * 9LL % mod * qpow(10, a[0] - 1) % mod;
            res = (tot - res + mod) % mod;
            cout << res << '\n';
        }
        
    } else {
        cout << 0 << '\n';
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
