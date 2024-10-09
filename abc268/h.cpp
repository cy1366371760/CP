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
	vector<int> adj[N];
	void init() {
		for (int i = 0; i <= tot; i++) {
			memset(nxt[i], 0, sizeof nxt[i]);
			fail[i] = 0;
			ed[i] = 0;
			adj[i].clear();
			vis[i] = 0;
		}
		tot = 1;
		id_mx = 0;	
	}
	vector<int> ins(string s, int id) {
		int n = s.length(), ps = 0, nw;
		vector<int> cur;
		cur.pb(ps);
		id_mx = max(id_mx, id);
		for (int i = 0; i < n; i++) {
			nw = s[i] - 'a';
			if (!nxt[ps][nw]) nxt[ps][nw] = tot++;
			ps = nxt[ps][nw];
			cur.pb(ps);
		}
		ed[ps] = 1;
		return cur;
	}
	void build() {
		int nw, nx, tmp;
		fail[0] = 0;
		vector<int> que;
		que.pb(0);
		for (int q = 0; q < que.size(); q++) {
			nw = que[q];
			for (int i = 0; i < 26; i++) {
				if (nxt[nw][i]) {
					nx = nxt[nw][i];
					if (!nw) fail[nx] = 0;
					else {
						tmp = fail[nw];
						while (tmp && !nxt[tmp][i]) tmp = fail[tmp];
						fail[nx] = nxt[tmp][i];
					}
					que.pb(nx);
				}
			}
		}
		for (int i = 1; i < tot; i++) {
			adj[fail[i]].pb(i);
		}
	}
	void match(string s) {
		int n = s.length(), ps = 0;
        int ans = 0;
		for (int i = 0; i < n; i++) {
			int nw = s[i] - 'a';
			while (ps && !nxt[ps][nw]) ps = fail[ps];
			ps = nxt[ps][nw];
			if (ed[ps]) {
                ++ans;
                ps = 0;
            }
		}
        cout << ans << nl;
	}
	void sol() {
		auto dfs = [&](auto &&self, int x) -> void {
            for (int y : adj[x]) {
                ed[y] |= ed[x];
                self(self, y);
            }
        };
        dfs(dfs, 0);
	}
}aho;
// usage: aho.init() aho.ins(), aho.build()

void solve() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    aho.init();
    for (int i = 1; i <= n; i++) {
        string t;
        cin >> t;
        aho.ins(t, i);
    }
    aho.build();
    aho.sol();
    aho.match(s);
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