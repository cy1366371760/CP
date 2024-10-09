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
const ll mod = 998244353;

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
    ll L, n;
    cin >> L >> n;
    ll may = L / 2;
    ll ans = 0;
    vector<ll> f(n + 5, 0);
    for (ll D = 1; D <= may; D++) { // strictly small than D
        ll gap = L - 2 * D;
        for (int num = 0; num < n; num++) {
            int del = num * gap;
            int remain = D - 1 - del;
            if (remain < n - 1) break;
            ll cur = C(remain, n - 1);
            int k = num + 1;
            int A = n - 1 - num * 2;
            cur = cur * C(2 * k + A - 1, 2 * k - 1) % mod;
            ans = (ans + cur) % mod;
        }
    }
    ans = ans * L % mod * qpow(n) % mod;
    cout << (may * C(L, n) % mod - ans + mod) % mod << nl;
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