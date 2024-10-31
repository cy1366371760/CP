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
    int n;
    cin >> n;
    vector<int> a(n + 5, 0);
    vector adj(n + 5, vector<int>());
    vector<int> stk;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        adj[a[i]].pb(i);
    }
    vector<int> sz(n + 5, 0);
    vector<int> ff(n + 5, -1);
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        sz[x] = 1;
        ff[x] = fa;
        for (int y : adj[x]) {
            if (y == fa) continue;
            self(self, y, x);
            sz[x] += sz[y];
        }
    };
    dfs(dfs, 0, -1);
    ll res = 1;
    for (int i = 0; i <= n; i++) {
        int remain = sz[i] - 1;
        sort(all(adj[i]), [&](int x, int y) {
            return x > y;
        });
        for (int j : adj[i]) {
            if (j == ff[i]) continue;
            res = res * C(remain - 1, sz[j] - 1) % mod;
            remain -= sz[j];
        }
    }
    cout << res << nl;
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