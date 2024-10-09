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
const int N = 4e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

#define VLL vector<ll>

ll qpow(ll x, ll y = mod - 2) {
	ll res = 1;
	while (y) {
		if (y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}

namespace Poly
{
	int wh[N], len, cc;
	void ntt(VLL &a, bool inv)
	{
		for(int i = 0; i < len; i++)
			if(i < wh[i])swap(a[i], a[wh[i]]);
		for(int l = 2; l <= len; l <<= 1)
		{
			int md = l >> 1;
			ll tp = qpow(3, (mod - 1) / l);
			for(int i = 0; i < len; i += l)
			{
				ll mo = 1;
				for(int j = 0; j < md; j++, mo = mo * tp % mod)
				{
					ll ha = mo * a[i + j + md] % mod;
					a[i + j + md] = (a[i + j] - ha + mod) % mod;
					a[i + j] = (a[i + j] + ha) % mod;
				}
			}
		}
		if(inv)
		{
			ll tmp = qpow(len);
			for(int i = 1; i < len / 2; i++)
				swap(a[i], a[len - i]);
			for(int i = 0; i < len; i++)
				a[i] = a[i] * tmp % mod;
		}
	}
	VLL mul(VLL x, VLL y)
	{
		cc = 0, len = 1;
		while(len < x.size() + y.size())
			++cc, len <<= 1;
		for(int i = 1; i < len; i++)
		{
			wh[i] = (wh[i >> 1] >> 1) | ((i & 1) << (cc - 1));
		}
		int bf = x.size() + y.size() - 1;
		x.resize(len);
		y.resize(len);
		ntt(x, 0), ntt(y, 0);
		for(int i = 0; i < len; i++)
			x[i] = x[i] * y[i] % mod;
		ntt(x, 1);
		x.resize(bf);
		return x;
	}
}


ll fac[N], ifac[N];

ll C(ll x, ll y) {
	if (x < y || y < 0) return 0;
	return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}

ll dp[2][1550][65];

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> p(26, 0);
    for (int i = 0; i < 26; i++) {
        cin >> p[i];
    }
    int g = (int)'g' - 'a';
    int e = (int)'e' - 'a';
    dp[0][0][2] = p[g] * p[g] % mod;
    vector<ll> res(n + 1, 0);
    ll ans = 0;
    for (int len = 2; len <= m + 5; len++) {
        ll ok = 0;
        int nw = len & 1;
        int nx = 1 - nw;
        for (int sec = 0; sec <= 60; sec++) {
            if (dp[nw][m][sec]) {
                ok = (ok + dp[nw][m][sec]) % mod;
            }
        }
        if (ok) {
            if (len <= n) (res[len] += ok) %= mod;
        }
        memset(dp[nx], 0, sizeof dp[nx]);
        for (int fir = 0; fir <= m; fir++) {
            for (int sec = 2; sec <= 60; sec++) {
                int nxt = fir + sec * (sec - 1) / 2;
                if (nxt > m) break;
                (dp[nx][nxt][sec] += dp[nw][fir][sec] * p[e]) %= mod;
                if (fir < m) (dp[nx][fir][sec + 1] += dp[nw][fir][sec] * p[g]) %= mod;
            }
        }
    }
    for (int dep = 0; dep < 2; dep++) {
        ll P = accumulate(all(p), 0LL) % mod;
        P = p[e] % mod;
        for (int mid = 0; mid < n; mid++) {
            (res[mid + 1] += res[mid] * P) %= mod;
        }
    }
    {
        ll P = accumulate(all(p), 0LL) % mod;
        P = p[g] % mod;
        for (int mid = 0; mid < n; mid++) {
            (res[mid + 1] += res[mid] * P) %= mod;
        }
        for (int i = 0; i <= n; i++) res[i] = res[i] * ifac[i] % mod;
        vector<ll> coef(n + 1, 0);
        ll Q = (accumulate(all(p), 0LL) - p[g] - p[e] + mod + mod) % mod;
        ll QL = 1;
        for (int i = 0; i <= n; i++) coef[i] = ifac[i] * QL % mod, QL = QL * Q % mod;
        res = Poly::mul(res, coef);
        for (int i = 0; i <= n; i++) {
            ll nw = res[i] * fac[i] % mod;
            nw = nw * (n - i + 1) % mod;
            ans = (ans + nw) % mod;
        }
        cout << ans << nl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 1e6;
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