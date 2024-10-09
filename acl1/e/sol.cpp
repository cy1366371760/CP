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


ll qpow(ll x, ll y = mod - 2) {
	ll res = 1;
	while (y) {
		if (y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}

struct Fen {
    vector<ll> a;
    int n;
    Fen(int n) {
        this->n = n;
        a.assign(n + 5, 0LL);
    }
    void add(int x, ll y) {
        for (; x <= n; x += x & -x) Add(a[x], y);
    }
    ll ask(int x) {
        ll res = 0;
        for (; x; x -= x & -x) Add(res, a[x]);
        return res;
    }
    ll ask(int l, int r) {
        return (ask(r) - ask(l - 1) + mod) % mod;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    // cerr << "??" << nl;
    ll res = 0;
    ll inv2 = qpow(2);
    Add(res, 1LL * k * (k - 1) / 2LL % mod * inv2);
    int d = 1;
    ll P = 1LL * (k - 1) * qpow(k) % mod;
    ll invP = qpow(P);
    ll cur = P, inv_cur = invP;
    Fen fen1(n), fen2(n);
    for (int i = 1; i <= k; i++) {
        fen1.add(p[i], inv_cur);
        fen2.add(p[i], 1);
    }
    // cerr << "!!" << nl;
    for (int i = k + 1; i <= n; i++) {
        ll nw = p[i];
        ++d;
        cur = cur * P % mod;
        inv_cur = inv_cur * invP % mod;
        ll small = fen1.ask(1, nw);
        Add(res, small * cur % mod * inv2);

        ll bigger = fen1.ask(nw + 1, n);
        ll big_num = fen2.ask(nw + 1, n);
        ll tmp = (big_num - bigger * cur % mod * inv2 % mod + mod) % mod;
        Add(res, tmp);
        
        fen1.add(nw, inv_cur);
        fen2.add(nw, 1);
    }
    cout << res << nl;
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