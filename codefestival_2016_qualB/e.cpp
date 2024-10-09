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

struct Aho {
	int nxt[N][26], fail[N], tot = 1, ed[N], vis[N], id_mx;
    int cnt[N], sz[N];
    pii fa[N], jp[N];
	vector<int> adj[N];
	void init() {
		for (int i = 0; i <= tot; i++) {
			memset(nxt[i], 0, sizeof nxt[i]);
			fail[i] = 0;
			ed[i] = 0;
			adj[i].clear();
			vis[i] = 0;
		}
        fa[0] = pii(-1, -1);
		tot = 1;
		id_mx = 0;	
	}
	int ins(string s, int id) {
		int n = s.length(), ps = 0, nw;
		vector<int> cur;
		cur.pb(ps);
		id_mx = max(id_mx, id);
		for (int i = 0; i < n; i++) {
			nw = s[i] - 'a';
			if (!nxt[ps][nw]) nxt[ps][nw] = tot++, fa[nxt[ps][nw]] = pii(ps, nw);
			ps = nxt[ps][nw];
			cur.pb(ps);
		}
		ed[ps] = id;
		return ps;
	}
	void build() {
        for (int i = tot - 1; i >= 0; i--) {
            cnt[i] = ed[i] > 0;
            for (int j = 0; j < 26; j++) {
                if (!nxt[i][j]) continue;
                cnt[i] += cnt[nxt[i][j]];
            }
        }
		for (int i = 0; i < tot; i++) {
            for (int j = 0; j < 26; j++) {
                if (nxt[i][j]) sz[i]++;
            }
            if (i == 0) {
                jp[0] = pii(-1, -1);
                continue;
            }

            if (sz[fa[i].fi] > 1 || ed[fa[i].fi]) jp[i] = pii(fa[i].fi, fa[i].sc);
            else jp[i] = jp[fa[i].fi];
        }
	}
	void sol(int nw, vector<int> order) {
		int k = 1;
        // cerr << "!!" << nw << nl;
        while (1) {
            int type;
            tie(nw, type) = jp[nw];
            // cerr << "GG" << nw << ' ' << type << nl;
            if (nw == -1) break;
            if (type != -1 && ed[nw]) {
                ++k;
            }
            if (type != -1) {
                for (int x : order) {
                    if (x == type) break;
                    if (nxt[nw][x]) k += cnt[nxt[nw][x]];
                }
            }
        }
        cout << k << nl;
	}
}aho;
// usage: aho.init() aho.ins(), aho.build()

void solve() {
    aho.init();
    int n;
    cin >> n;
    aho.init();
    vector<int> ed(n + 1);
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        ed[i] = aho.ins(s, i);
    }
    aho.build();
    int qq;
    cin >> qq;
    while (qq--) {
        int k; string s;
        cin >> k >> s;
        vector<int> order;
        for (int i = 0; i < s.length(); i++) {
            order.pb(s[i] - 'a');
        }
        aho.sol(ed[k], order);
    }
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