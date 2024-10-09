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
const int N = 2e6 + 100;
const ll inf = 1e18;
const ll mod = 1e9 + 7;

ll fac[N], ifac[N];
ll qpow(ll x, ll y = mod - 2) {
	ll res = 1;
	while (y) {
		if (y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}
ll C(ll x, ll y) {
	if (x < y || y < 0) return 0;
	return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}

void solve() {
    int n, h;
    cin >> n >> h;
    vector<int> cnt(h + 1, 0);
    for (int i = 1; i <= h; i++) {
        cin >> cnt[i];
        cnt[i] += cnt[i - 1];
    }
    vector<ll> f(h + 1, 0);
    for (int i = 1; i <= h; i++) {
        int nw = cnt[i];
        f[i] = fac[nw] * fac[n - nw] % mod;
        // cerr << "??" << i << ' ' << f[i] << nl;
    }
    vector<ll> g(h + 1, 0);
    for (int i = h; i >= 1; i--) {
        g[i] = f[i];
        for (int j = i + 1; j <= h; j++) {
            g[i] = (g[i] - g[j] * fac[cnt[j] - cnt[i]] % mod * fac[cnt[i]] % mod * ifac[cnt[j]] % mod + mod) % mod;
        }
    }
    ll tot = fac[n];
    for (int i = 1; i <= h; i++) {
        tot = (tot - g[i] + mod) % mod;
    }
    cout << tot << nl;
}

signed main() {
    int n = 2e6;
	fac[0] = 1;
	for (int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i % mod;
	}
	ifac[n] = qpow(fac[n]);
	for (int i = n - 1; i >= 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1) % mod;
	}
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}