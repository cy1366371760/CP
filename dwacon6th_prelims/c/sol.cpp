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

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(k + 1);
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
    }
    vector<ll> dp(n + 5, 0);
    dp[0] = 1;
    for (int i = 1; i <= k; i++) {
        vector<ll> dq(n + 5, 0);
        for (int v = 0; v <= n; v++) {
            if (!dp[v]) continue;
            for (int nw = 0; nw <= a[i] && nw + v <= n; nw++) {
                Add(dq[v + nw], dp[v] * C(n - v, nw) % mod * C(n - nw, a[i] - nw) % mod);
            }
        }
        swap(dp, dq);
    }
    cout << dp[n] << nl;
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