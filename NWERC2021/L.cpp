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

ll fac[N], ifac[N];
ld qpow(ld x, ll y) {
	ld res = 1;
	while (y) {
		if (y & 1) res = res * x;
		x = x * x;
		y >>= 1;
	}
	return res;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<ld> g(n + 1, 0), f(n + 1, 0);
    for (int mx = 1; mx <= n; mx++) {
        ld tmp = (ld)1.0 * mx / n;
        g[mx] = qpow(tmp, k);
        f[mx] = (g[mx] - g[mx - 1]);
    }
    ld res = 0;
    for (int i = 1; i <= n; i++) {
        if (i < m) res += m * f[i];
        else res += (1.0 + i) / 2.0 * f[i];
    }
    cout << fixed << setprecision(10) << res << nl;
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