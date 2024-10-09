#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define pii pair<int, int>
#define fi first
#define sc second
using namespace std;
const int inf = 1e9;
const int N = 4e6 + 100;
const ll mod = 998244353;

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
VLL diff(VLL a, int n) {
	a.resize(n - 1);
	for (int i = 0; i < n - 1; i++) a[i] = a[i + 1] * (i + 1) % mod;
	return a;
}
VLL integ(VLL a, int n) {
	a.resize(n + 1);
	for (int i = n; i; i--) a[i] = a[i - 1] * ifac[i] % mod * fac[i - 1] % mod; // inv[i] =  (ifac[i] * fac[i - 1])
	return a[0] = 0, a;
}
VLL ln(VLL a, int n) {
	VLL b = inv(a, n);
	a = diff(a, n), pre_ntt(n << 1);
	ntt(a, 1), ntt(b, 1);
	for (int i = 0; i < limit; i++) a[i] = a[i] * b[i] % mod;
	ntt(a, 0), a.resize(n - 1);
	return integ(a, n - 1);
}
VLL exp(VLL a, int n) {
	if (n == 1) return {1};
	a.resize(n); VLL b = exp(a, (n + 1) >> 1), c;
	c = ln(b, n + 1), b.resize(n);
	pre_ntt(n + 1);
	for (int i = 0; i < n; i++) a[i] = upd(a[i] - c[i] + (!i));
	c = b, ntt(a, 1), ntt(c, 1);
	for (int i = 0; i < limit; i++) a[i] = a[i] * c[i] % mod;
	ntt(a, 0), a.resize(n);
	for (int i = (n + 1) >> 1; i < n; i++) b[i] = a[i];
	return b;
}
}
using namespace Poly;