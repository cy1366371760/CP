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

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}

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
    int n;
    cin >> n;
    vector adj(n + 1, vector<int>());
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].pb(i);
    }
    vector dp(n + 5, vector<ll>(n + 5, 0));
    vector<int> sz(n + 5, 0);
    auto dfs = [&](auto &&self, int x) -> void {
        sz[x] = 0;
        dp[x][0] = 1;
        for (int y : adj[x]) {
            self(self, y);
            vector<ll> nxt(sz[x] + sz[y] + 1, 0);
            for (int sz1 = 0; sz1 <= sz[x]; sz1++) {
                for (int sz2 = 0; sz2 <= sz[y]; sz2++) {
                    Add(nxt[sz1 + sz2], dp[x][sz1] * dp[y][sz2]);
                }
            }
            sz[x] += sz[y];
            for (int i = 0; i <= sz[x]; i++) {
                dp[x][i] = nxt[i];
            }
        }
        for (int i = 1; i <= sz[x]; i++) {
            Add(dp[x][i - 1], (mod - 1) * dp[x][i] % mod * i % mod);
        }
        ++sz[x];
        for (int i = sz[x]; i >= 1; i--) {
            dp[x][i] = dp[x][i - 1];
        }
        dp[x][0] = 0;
    };
    dfs(dfs, 1);
    ll ans = 0;
    for (int i = 0; i <= sz[1]; i++) {
        Add(ans, dp[1][i] * fac[i] % mod);
    }
    cout << ans << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 2e6;
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