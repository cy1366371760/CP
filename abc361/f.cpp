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

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res *= a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> may;
    for (ll b = 3; b <= 60; b++) {
        bool prime = 1;
        for (ll d = 2; d * d <= b; d++) {
            if (b % d == 0) {
                prime = 0;
                break;
            }
        }
        if (!prime) continue;
        ll lim = powl(n, 1.0 / b) + 10;
        while (powl(lim, b) > n) lim--;
        for (ll a = 2; a <= lim; a++) {
            ll val = qpow(a, b);
            may.pb(val);
        }
    }
    sort(all(may));
    may.erase(unique(all(may)), may.end());
    ll ans = may.size();
    ll sn = sqrtl(n);
    while ((sn + 1) * (sn + 1) <= n) sn++;
    while (sn * sn > n) sn--;
    ans += sn;
    for (ll val : may) {
        ll sv = sqrtl(val);
        for (ll i = max(0LL, sv - 10); i <= sv + 10; i++) {
            if (i * i == val) {
                ans--;
                break;
            }
        }
    }
    cout << ans << '\n';
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
