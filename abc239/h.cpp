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
const ll mod = 1e9 + 7;

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
    int n, m;
    cin >> n >> m;
    ++m;
    int B = sqrt(m) + 5;
    unordered_map<int, int> ps;
    vector<int> vals(2 * B + 10, 0);
    int num = 0;
    for (int l = 1, r; l <= m; l = r + 1) {
        int x = (m + l - 1) / l;
        if (x != 1) r = (m - 1) / (x - 1);
        else r = l;
        vals[++num] = x;
        ps[x] = num;
    }
    auto pos = [&](int x) {
        return ps[x];
    };
    vector<ll> dp(num + 5, 0);
    for (int i = num; i >= 1; i--) {
        int nw = pos(vals[i]);
        int v = vals[i];
        if (v == 1) {
            dp[nw] = 0;
            continue;
        }
        dp[nw] = 0;
        for (int l = 1, r; l <= v && l <= n; l = r + 1) {
            int x = (v + l - 1) / l;
            if (x != 1) r = (v - 1) / (x - 1);
            else r = l;
            r = min(r, n);
            if (x == v) continue;
            // cerr << "!!" << v << ' ' << x << ' ' << l << ' ' << r << nl;
            // exit(0);
            int to = pos(x);
            dp[nw] = (dp[nw] + dp[to] * (r - l + 1)) % mod;
        }
        dp[nw] = (dp[nw] + n) * qpow(n - 1) % mod;
        // cerr << nw << ' ' << v << ' ' << dp[nw] << nl;
    }
    cout << dp[1] << nl;
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