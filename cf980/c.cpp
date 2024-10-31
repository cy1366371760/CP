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
const pll bas = pll(1e6 + 3, 1e6 + 7);
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
	void init(vector<int> s) { // only use 1 to n - 1 (0 must be '#')
		n = s.size() - 1;
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
}hsh[2][2];

void solve() {
    int n, k;
    cin >> n >> k;
    vector ot(2, vector<int>(n + 5, 0));
    vector adj(2, vector(n + 5, vector<int>()));
    auto bfs = [&](auto &adj, int st) {
        vector<int> que;
        vector<bool> vis(n + 5, 0);
        vector<int> col(n + 5, 0);
        vis[st] = 1, col[st] = 0;
        que.pb(st);
        for (int q = 0; q < que.size(); q++) {
            int x = que[q];
            for (int y : adj[x]) {
                if (!vis[y]) {
                    vis[y] = 1;
                    col[y] = (col[x] + 1) % k;
                    que.pb(y);
                }
            }
        }
        return col;
    };
    vector cnt(2, vector(2, vector<int>(2 * k + 1, 0)));
    for (int type = 0; type < 2; type++) {
        for (int i = 1; i <= n; i++) {
            cin >> ot[type][i];
        }
        int m;
        cin >> m;
        for (int i = 1; i <= m; i++) {
            int x, y;
            cin >> x >> y;
            adj[type][x].pb(y);
        }
        auto col = bfs(adj[type], 1);
        for (int i = 1; i <= n; i++) {
            ++cnt[type][ot[type][i]][col[i] + 1];
        }
    }
    if (accumulate(all(ot[0]), 0) == 0 && accumulate(all(ot[1]), 0) == n) {
        cout << "YES" << nl;
        return;
    }
    if (accumulate(all(ot[0]), 0) == n && accumulate(all(ot[1]), 0) == 0) {
        cout << "YES" << nl;
        return;
    }
    for (int i = k + 1; i <= 2 * k; i++) {
        cnt[0][0][i] = cnt[0][0][i - k];
        cnt[0][1][i] = cnt[0][1][i - k];
        cnt[1][0][i] = cnt[1][0][i - k];
        cnt[1][1][i] = cnt[1][1][i - k];
    }
    hsh[0][0].init(cnt[0][0]);
    hsh[0][1].init(cnt[0][1]);
    hsh[1][0].init(cnt[1][0]);
    hsh[1][1].init(cnt[1][1]);
    for (int bias = 0; bias < k; bias++) {
        // 00 <=> 1,bias
        bool ok = 1;
        {
            auto lhs = hsh[0][1].ask(1, k);
            auto rhs = hsh[1][0].ask(1 + bias + 1, k + bias + 1);
            ok &= (lhs == rhs);
        }
        {
            auto lhs = hsh[0][0].ask(2, k + 1);
            auto rhs = hsh[1][1].ask(2 + bias - 1, k + 1 + bias - 1);
            ok &= (lhs == rhs);
        }
        if (ok) {
            cout << "YES" << nl;
            return;
        }
    }
    cout << "NO" << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}