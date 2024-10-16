#include<bits/stdc++.h>

#define nl '\n'
#define ll long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define fi first
#define sc second
#define int long long
#define pii pair<int, int>
#define pll pair<ll, ll>
template<typename T> bool chkmin(T &a, T b){return (b < a) ? a = b, 1 : 0;}
template<typename T> bool chkmax(T &a, T b){return (b > a) ? a = b, 1 : 0;}
using namespace std;
using ld = long double;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

int np[N], mu[N], coef[N];
int pri[N];
int pnum = 0;
vector<int> factor[N];

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
    int n;
    cin >> n;
    const int m = 1e5;
    vector<ll> cnt(m + 10, 0);
    ll tmp = 1;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        ans = (ans * 2) % mod;
        for (int y : factor[x]) {
            ans = (ans + cnt[y] * coef[y]) % mod;
        }
        for (int y : factor[x]) {
            cnt[y] = (cnt[y] + tmp) % mod;
        }
        tmp = tmp * 2 % mod;
        cout << ans << nl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n = 1e6;
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!np[i]) {
            pri[++pnum] = i;
            np[i] = i;
            mu[i] = (mod - 1);
        } 
        for (int j = 1; j <= pnum && 1LL * i * pri[j] <= n; j++) {
            np[i * pri[j]] = pri[j];
            if (i % pri[j] == 0) {
                mu[i * pri[j]] = 0;
                break;
            }
            mu[i * pri[j]] = (mod - 1) * mu[i] % mod;
        }
    }
    n = 1e5;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; 1LL * j * j <= i; j++) {
            if (i % j == 0) {
                factor[i].pb(j);
                coef[i] = (coef[i] + j * mu[i / j]) % mod;
                if (i != 1LL * j * j) {
                    factor[i].pb(i / j);
                    coef[i] = (coef[i] + (i / j) * mu[j]) % mod;
                }
            }
        }
    }
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}