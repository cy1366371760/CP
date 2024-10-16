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

ll qpow(ll x, ll y = mod - 2) {
	ll res = 1;
	while (y) {
		if (y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}

namespace Poly{
ll upd(ll x) { return x + (x >> 63 & mod); }

#define VLL vector<ll>
int limit;
ll omg[N];

void pre_ntt(int len) {
	for (limit = 1; limit < len; limit <<= 1) ;
	static int L = 1;
	for (int &i = L; i < limit; i <<= 1) {
		omg[i] = 1; int w = qpow(3, mod / 2 / i);
		for (int j = 1; j < i; j++) omg[i + j] = omg[i + j - 1] * w % mod;
	}
}
void dft(VLL &p) {
	for (int i = limit >> 1, s = limit; i; i >>= 1, s >>= 1)
		for (int j = 0; j < limit; j += s) for (int k = 0, o = i; k < i; ++k, ++o) {
			int x = p[j + k], y = p[i + j + k];
			p[j + k] = upd(x + y - mod), p[i + j + k] = omg[o] * upd(x - y) % mod;
		}
}
void idft(VLL &p) {
	for (int i = 1, s = 2; i < limit; i <<= 1, s <<= 1)
		for (int j = 0; j < limit; j += s) for (int k = 0, o = i; k < i; ++k, ++o) {
			int x = p[j + k], y = omg[o] * p[i + j + k] % mod;
			p[j + k] = upd(x + y - mod), p[i + j + k] = upd(x - y);
		}
	reverse(p.begin() + 1, p.end());
	for (int i = 0, inv = qpow(limit, mod - 2); i < limit; i++) p[i] = p[i] * inv % mod;
}
void ntt(VLL &p, int op) {
	p.resize(limit);
	if (op == 1) dft(p);
	else idft(p);
}
VLL operator * (VLL a, VLL b) {
	int len = a.size() + b.size();
	pre_ntt(len);
	ntt(a, 1), ntt(b, 1);
	for (int i = 0; i < limit; i++) a[i] = a[i] * b[i] % mod;
	ntt(a, 0), a.resize(len);
	return a;
}
VLL operator + (VLL a, const VLL &b) {
	a.resize(max(a.size(), b.size()));
	for (int i = 0; i < a.size(); i++)
		a[i] = upd(a[i] + (i < b.size() ? b[i] : 0) - mod);
	return a;
}
VLL operator - (VLL a, const VLL &b) {
	a.resize(max(a.size(), b.size()));
	for (int i = 0; i < a.size(); i++)
		a[i] = upd(a[i] - (i < b.size() ? b[i] : 0));
	return a;
}
VLL inv(VLL a, int n = -1) {
    VLL res(1), t, t2;
    assert(a[0]);
	res[0] = qpow(a[0], mod - 2);
    for (int l = 1; l < a.size(); l <<= 1) {
    	t2 = a, t2.resize(l << 1);
		t = t2 * res, t.resize(l << 1), t = t * res, t.resize(l << 1);
        res = res + res - t;
	}
    return res.resize(a.size()), res;
}
}
using namespace Poly;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n + 5);
    const int m = 1e6;
    VLL cnt(m + 10, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]] += 1;
    }
    for (int i = 0; i <= m; i++) {
        chkmin(cnt[i], 3LL);
    }
    VLL f = cnt * cnt;
    for (int i = 0; i <= m; i++) {
        f[i + i] = f[i + i] - cnt[i] * cnt[i];
    }
    for (int i = 0; i < f.size(); i++) f[i] = f[i] / 2;
    for (int i = 0; i <= m; i++) {
        f[i + i] = f[i + i] + cnt[i] * (cnt[i] - 1) / 2;
    }
    for (int i = 1; i <= n; i++) {
        int nw = a[i];
        int need = x - nw;
        ll delta = 0;
        int need2 = need - nw;
        if (need2 >= 0 && need2 == nw) {
            delta = cnt[need2] - 1;
        } else if (need2 >= 0) {
            delta = cnt[need2];
        } else delta = 0;
        if (delta == f[need]) {
            continue;
        }
        // cerr << i << ' ' << a[i] << ' ' << delta << ' ' << f[need] << ' ' << need2 << ' ' << cnt[need2] << nl;
        vector<int> las(m + 100, 0);
        for (int j = n; j > i; j--) {
            int want = need - a[j];
            if (want >= 0 && las[want] != 0) {
                cout << i << ' ' << j << ' ' << las[want] << nl;
                break;
            }
            las[a[j]] = j;
        }
        exit(0);
    }
    cout << -1 << nl;
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