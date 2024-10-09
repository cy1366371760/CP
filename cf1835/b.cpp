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

const int Hash_mod = 1e6 + 100;
struct Hash_table {
	vector<vector<pll>> buk;
    Hash_table() {
        buk.resize(Hash_mod);
    }
	void ins(ll x) {
        // cerr << "!!" << nl;
        int wh = x % Hash_mod;
        for (auto &[u, v]: buk[wh]) {
            if (x == u) {
                ++v;
                return;
            }
        }
		buk[wh].pb({x, 1LL});
	}
	int find(ll x) {
        // cerr << "??" << nl;
		int wh = x % Hash_mod;
		for (int i = buk[wh].size() - 1; i >= 0; i--) {
			if (buk[wh][i].fi == x) {
				return buk[wh][i].sc;
			}
		} 
		return 0;
	}
};

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(all(a));
    ll mx = 0, ps = 0;
    auto upd = [&](ll val, ll cur) {
        if (val > mx || (val == mx && cur < ps)) {
            mx = val;
            ps = cur;
        }
        return;
    };
    auto ask_l = [&](int id, ll val) {
        if (id < 0) return (val - 1) - 0 + 1;
        ll lb = a[id];
        ll rb = val;
        ll gap = (rb - lb - 1);
        return gap / 2;
    };
    auto ask_r = [&](int id, ll val) {
        if (id >= n) return m - (val + 1) + 1;
        ll lb = val;
        ll rb = a[id];
        ll gap = (rb - lb - 1);
        return gap / 2;
    };
    {
        ps = 0;
        ll rhs = 0;
        if (k <= n) rhs = ask_r(k - 1, 0);
        else rhs = m;
        int c0 = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 0) {
                c0++;
            } else break;
        }
        if (c0 >= k) mx = 0;
        else mx = rhs + 1;
    }
    for (int type = 0; type < 2; type++) {
        Hash_table cnt;
        for (int i = 0; i < n; i++) {
            cnt.ins(a[i]);
        }
        for (int i = 0; i < n; i++) {
            ll nw = a[i];
            // select (nw + 1)
            if (i == n - 1) {
                if (nw == m) continue;
                ll sel = nw + 1;
                ll lhs = ask_l(i - k + 1, sel);
                ll rhs = m - sel;
                upd(lhs + rhs + 1, type ? m - sel : sel);
                if (nw < m - 1) {
                   ll sel = nw + 2;
                   ll lhs = ask_l(i - k + 1, sel);
                   ll rhs = m - sel;
                   upd(lhs + rhs + 1, type ? m - sel : sel);
                }
                break;
            }
            if (a[i + 1] != a[i]) {
                ll sel = nw + 1;
                ll remain = k - cnt.find(sel);
                if (remain <= 0) continue;
                ll lhs = ask_l(i - remain + 1, sel);
                ll rhs = ask_r(i + 1 + k - 1, sel);
                upd(lhs + rhs + 1, type ? m - sel: sel);
            }
            if (a[i + 1] > a[i] + 1) {
                ll sel = nw + 2;
                ll remain = k - cnt.find(sel);
                if (remain <= 0) continue;
                ll lhs = ask_l(i - remain + 1, sel);
                ll rhs = ask_r(i + 1 + k - 1, sel);
                upd(lhs + rhs + 1, type ? m - sel: sel);
            }
        }
        for (ll &x : a) {
            x = m - x;
        }
        reverse(all(a));
    }
    cout << mx << ' ' << ps << nl;
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