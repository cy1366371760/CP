const pll mod = pll(1e9 + 7, 1e9 + 9);
const pll bas = pll(137, 139);
pll operator *(pll a, pll b) {
	return pll(a.fi * b.fi % mod.fi, a.sc * b.sc % mod.sc);
}
pll operator +(pll a, pll b) {
	return pll((a.fi + b.fi) % mod.fi, (a.sc + b.sc) % mod.sc);
}
pll operator -(pll a, pll b) {
	return pll((a.fi + mod.fi - b.fi) % mod.fi, (a.sc + mod.sc - b.sc) % mod.sc);
}
struct Hash {
	vector<pll> val;
	vector<pll> pw_bas;
	pll mg(pll a, pll b, int len_b) {
		return a * pw_bas[len_b] + b;
	}
	int n;
	void init(string s) { // only use 1 to n - 1 (0 must be '#')
		n = s.length() - 1;
		val.resize(n + 2);
		pw_bas.resize(n + 2);
		pw_bas[0] = pll(1, 1);
		for (int i = 1; i <= n; i++) {
			pw_bas[i] = pw_bas[i - 1] * bas;
		}
		val[0] = pll(0, 0);
		for (int i = 1; i <= n; i++) {
			val[i] = val[i - 1] * bas + pll(s[i], s[i]);
		}
	}
	pll ask(int l, int r) {
		return val[r] - val[l - 1] * pw_bas[r - l + 1];
	}
}hsh;