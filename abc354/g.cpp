#include<bits/stdc++.h>

#define ll long long
#define int long long
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

struct Dinic {
	int s, t;
	int hed[N], cur[N], dep[N], nxt[N], las[N], to[N], cnt;
	bool bfs() {   
		memset(dep, 0, (t + 5) * sizeof (int));
		dep[s] = 1;
		vector<int> que;
		que.pb(s);
		for (int q = 0; q < que.size(); q++) {
			int nw = que[q];
			for (int i = hed[nw]; ~i; i = nxt[i]) {
				if (!dep[to[i]] && las[i]) {
					dep[to[i]] = dep[nw] + 1;
					que.pb(to[i]);
				}
			}
		}
		return dep[t];
	}
	int dfs(int ps,int flow) {
	    if(ps == t) return flow;
	    for (int &i = cur[ps]; ~i; i = nxt[i]) {
	    	if (dep[to[i]] == dep[ps] + 1 && las[i]) {
	    		int nw = dfs(to[i], min(flow, las[i]));
	    		if (nw) {
	    			las[i] -= nw;
	    			las[i ^ 1] += nw;
	    			return nw;
				}
			}
	    }   
	    return 0;
	}
	void add_edge(int u,int v,int w)//加边
	{
	    nxt[++cnt] = hed[u], las[cnt] = w, to[cnt] = v, hed[u] = cnt;
	    nxt[++cnt] = hed[v], las[cnt] = 0, to[cnt] = u, hed[v] = cnt;
	}
	void init(int _s, int _t)
	{
	    memset(nxt,-1,sizeof nxt);
	    memset(hed,-1,sizeof hed);
	    cnt = -1;
	    s = _s, t = _t;
	    return;
	}
	ll max_flow() {
		ll flow = 0;
		while (bfs()) {
			for (int i = 0; i <= t; i++) cur[i] = hed[i];
			ll tmp;
			while ((tmp = dfs(s, inf)) != 0) {
				flow += tmp;
			}
		}
		return flow;
	}
}dinic;

void solve() {
    int n;
    cin >> n;
    vector<string> s(n);
    ll ss = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        s[i] = '#' + s[i];
    }
    vector<ll> val(n);
    for (int i = 0; i < n; i++) cin >> val[i], ss += val[i];
    auto is_substr = [&](string a, string b) {
        if (a.length() > b.length())swap(a, b);
        int la = a.length() - 1;
        hsh.init(a);
        pll hsh_a = hsh.ask(1, a.length() - 1);
        hsh.init(b);
        for (int i = 1; i + la - 1 < b.length(); i++) {
            if (hsh.ask(i, i + la - 1) == hsh_a) return 1;
        }
        return 0;
    };
    int _s = 2 * n + 5, _t = 2 * n + 6;
    dinic.init(_s, _t);
    int cnt = n;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (is_substr(s[i], s[j])) {
                if (s[i].length() <= s[j].length()) {
                    dinic.add_edge(i, j + n, 1e18);
                    // cerr << i << ' ' << j + n << '\n';
                } else {
                    dinic.add_edge(j, i + n, 1e18);
                    // cerr << j << ' ' << i + n << '\n';
                }
            } 
        }
    }
    for (int i = 0; i < n; i++) {
        dinic.add_edge(_s, i, val[i]);
        dinic.add_edge(i + n, _t, val[i]);
        // cerr << _s << ' ' << i << ' ' << i + n << ' ' << _t <<  ' ' << val[i] << '\n';
    }
    ll ans = dinic.max_flow();
    // cerr << ans << '\n';
    cout << ss - ans << '\n';
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
