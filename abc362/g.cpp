#include<bits/stdc++.h>

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
const ll mod = 998244353;
const int inf = 1e9;

const int MAX_SEG_V = 5e5;
template<class Info>
struct SegT {
	#define mid ((l + r) >> 1)
	#define nls seg[nw].ls
	#define nrs seg[nw].rs
	struct Node {
		int ls = 0, rs = 0;
		Info val;
	}seg[N * 20];
	int tot = 0;
	void push_up(int nw) {
		seg[nw].val = Info{};
		if (nls) seg[nw].val = seg[nw].val + seg[nls].val;
		if (nrs) seg[nw].val = seg[nw].val + seg[nrs].val;
	}
	int ins(int to, Info val, int l = 1, int r = MAX_SEG_V) {
		int nw = ++tot;
		if (l == r) {
			seg[nw].val = val;
			return nw;
		}
		if (to <= mid) {
			nls = ins(to, val, l, mid);
		} else {
			nrs = ins(to, val, mid + 1, r);
		}
		push_up(nw);
		return nw;
	}
	int mg(int a, int b) {
		if (!a || !b) return a + b;
		seg[a].val = seg[a].val + seg[b].val;
		if (seg[a].ls || seg[b].ls) {
			seg[a].ls = mg(seg[a].ls, seg[b].ls);
		}
		if (seg[a].rs || seg[b].rs) {
			seg[a].rs = mg(seg[a].rs, seg[b].rs);
		}
		return a;
	}
	Info ask(int nw, int L, int R, int l = 1, int r = MAX_SEG_V) {
		if (!nw) return Info{};
		if (l > R || r < L) {
			return Info{};
		}
		if (L <= l && r <= R) {
			return seg[nw].val;
		}
		return ask(nls, L, R, l, mid) + ask(nrs, L, R, mid + 1, r);
	}
	#undef mid
	#undef nls
	#undef nrs
};
struct Info {
	int v = 0;
};
Info operator +(Info a, Info b) {
	return {a.v + b.v};
}

const int SAM_SZ = 2e6 + 100;
struct SAM {
    int ocr[SAM_SZ][2]; // 多串改map
	int tot, las, nxt[SAM_SZ][26], fa[SAM_SZ], mx[SAM_SZ], mx_ed[SAM_SZ];
	vector<int> adj[SAM_SZ]; // fail tree (parent tree), edge sorted in lexi order for suffix tree
	void init() {
		for (int i = 0; i <= tot; i++) {
			memset(nxt[i], 0, sizeof nxt[i]);
			fa[i] = mx[i] = 0;
			ocr[i][0] = ocr[i][1] = 0;
			mx_ed[i] = -1;	
			adj[i].clear();
		}
		tot = 1, las = 1;
	}
	int mn(int p) {
		return mx[fa[p]] + 1;
	}
	void ins(int x, int op = 0, int ps = -1) {
		int p = las, np = nxt[las][x], t, nt;
		if (np) { // 广义用
			if (mx[p] + 1 == mx[np]) {
				las = np;
				ocr[np][op]++;
			} else {
				nt = ++tot;
				mx[nt] = mx[p] + 1;
				memcpy(nxt[nt], nxt[np], sizeof nxt[np]);
				fa[nt] = fa[np], fa[np] = nt;
				while (p && nxt[p][x] == np) {
					nxt[p][x] = nt, p = fa[p];
				}
				ocr[nt][op]++;
				las = nt;
			}
			return;
		}
		np = ++tot, mx[np] = mx[p] + 1;
		las = np, ocr[np][op]++, mx_ed[np] = ps;
		while (p && !nxt[p][x]) {
			nxt[p][x] = np;
			p = fa[p];
		}
		if (!p) {
			fa[np] = 1;
			return;
		}
		t = nxt[p][x];
		if (mx[t] == mx[p] + 1) {
			fa[np] = t;
		} else {
			nt = ++tot, mx[nt] = mx[p] + 1;
			memcpy(nxt[nt], nxt[t], sizeof nxt[t]);
			fa[nt] = fa[t], fa[t] = fa[np] = nt;
			while (p && nxt[p][x] == t) {
				nxt[p][x] = nt;
				p = fa[p];
			}
		}
	}
	void build_edge(string &s) { // 出边满足后缀树字典序，需要插入反串
		for (int i = 2; i <= tot; i++) {
			adj[fa[i]].pb(i);
		}
		auto dfs = [&](auto self, int x) -> void{
			for (int y : adj[x]) {
				self(self, y);
				mx_ed[x] = max(mx_ed[x], mx_ed[y]);
			}
		};
		dfs(dfs, 1);
		for (int i = 1; i <= tot; i++) {
			sort(all(adj[i]), [&](int x, int y) {
				int cx = s[mx_ed[x] - mx[i]];
				int cy = s[mx_ed[y] - mx[i]];
				return cx < cy;	
			});
		}
	}
	void build(string &s) {
		init();
		for (int i = 0; i < s.length(); i++) {
			ins(s[i] - 'a', 0, i);
		}
		build_edge(s);
	}
	void match(string t) {
		vector<int> cur;
		int nw = 1, cur_len = 0;
		cur.pb(nw);
		for (int i = 0; i < t.length(); i++) {
			int x = t[i] - 'a';
			while (nw > 1 && !nxt[nw][x]) {
				nw = fa[nw];
				cur_len = mx[nw];
			}
			if (nxt[nw][x]) nw = nxt[nw][x], cur_len++;
			cur.pb(nw);
		}
        if (cur_len == t.length()) {
            cout << ocr[nw][0] << '\n';
        } else {
            cout << 0 << '\n';
        }
	}
	void sol(int n) {
        auto dfs = [&](auto self, int x) -> void{
			for (int y : adj[x]) {
				self(self, y);
                ocr[x][0] += ocr[y][0];
			}
		};
        dfs(dfs, 1);
	}
}sam;

void solve() {
    sam.init();
    string s;
    cin >> s;
    sam.build(s);
    sam.sol(s.length());
    int t;
    cin >> t;
    vector<string> qry(t);
    for (int i = 0; i < t; i++) {
        cin >> qry[i];
        sam.match(qry[i]);
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
