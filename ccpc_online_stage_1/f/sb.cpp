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
const int N = 1e6 + 100;
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
    auto Add_ans = [&](ll k, ll ok) {
        ll P = accumulate(all(p), 0LL) % mod;
        P = (P - p[e] - p[g] + mod + mod) % mod;
        ll PL = 1;
        for (int mid = 0; mid + k <= n; mid++) {
            ll cur = PL * ok % mod;
            (res[mid + k] += cur * C(mid + k - 3, k - 3)) %= mod;
            PL = PL * P % mod;
        }
    };
    for (int len = 2; len <= m + 5; len++) {
        ll ok = 0;
        int nw = len & 1;
        int nx = 1 - nw;
        for (int sec = 0; sec < 65; sec++) {
            if (dp[nw][m][sec]) {
                ok = (ok + dp[nw][m][sec]) % mod;
            }
        }
        if (ok) {
            Add_ans(len, ok);
        }
        memset(dp[nx], 0, sizeof dp[nx]);
        for (int fir = 0; fir <= m; fir++) {
            for (int sec = 2; sec <= 64; sec++) {
                int nxt = fir + sec * (sec - 1) / 2;
                if (nxt > m) break;
                (dp[nx][nxt][sec] += dp[nw][fir][sec] * p[e]) %= mod;
                if (fir < m) (dp[nx][fir][sec + 1] += dp[nw][fir][sec] * p[g]) %= mod;
            }
        }
    }
    for (int dep = 0; dep < 2; dep++) {
        ll P = accumulate(all(p), 0LL) % mod;
        P = (P - p[g] + mod + mod) % mod;
        for (int mid = 0; mid < n; mid++) {
            (res[mid + 1] += res[mid] * P) %= mod;
        }
    }
    {
        ll P = accumulate(all(p), 0LL) % mod;
        P = (P - p[e] + mod + mod) % mod;
        for (int mid = 0; mid < n; mid++) {
            (res[mid + 1] += res[mid] * P) %= mod;
        }
        for (int i = 0; i <= n; i++) {
            ans = (ans + res[i] * (n - i + 1)) % mod;
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