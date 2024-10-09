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

void solve() {
    string s;
    cin >> s;
    int n = s.length();
    s = '#' + s;
    hsh.init(s);
    pll ini = hsh.ask(1, n);
    int nw = 0;
    for (int i = 1; i <= n; i++) {
        if (nw == 0 && i > 1) {
            pll fir = hsh.ask(i, n);
            pll sec = hsh.ask(1, i - 1);
            pll gain = hsh.mg(fir, sec, i - 1);
            if (gain != ini) {
                for (int j = i; j <= n; j++) cout << s[j];
                for (int j = 1; j < i; j++) cout << s[j];
                return;
            }
        }
        nw += (s[i] == '(' ? 1 : -1);
    }
    cout << "no" << nl;
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