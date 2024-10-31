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
const int inf = 1e9;
const ll mod = 998244353;

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
			while ((tmp = dfs(s, (int)1e9)) != 0) {
				flow += tmp;
			}
		}
		return flow;
	}
}dinic;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> exact(30, -1);
    vector<int> mn_need(30, 0);
    vector<int> ans(m + 5, -1);
    vector cant(m + 5, vector<int> (30, 0));
    auto upd = [&](string s, string t) {
        vector<int> cnt_G(30, 0), cnt_Y(30, 0), cnt_B(30, 0);
        vector<int> ocr_B(30, 0);
        for (int i = 1; i <= m; i++) {
            int nw = s[i] - 'a';
            if (t[i] == 'G') {
                cnt_G[nw]++;
                ans[i] = nw;
            } else if (t[i] == 'Y') {
                cnt_Y[nw]++;
                cant[i][nw] = 1;
            } else {
                cnt_B[nw]++;
                cant[i][nw] = 1;
                ocr_B[nw] = 1;
            }
        }
        for (int c = 0; c < 26; c++) {
            if (ocr_B[c]) {
                exact[c] = cnt_G[c] + cnt_Y[c];
            } else {
                mn_need[c] = max(mn_need[c], cnt_G[c] + cnt_Y[c]);
            }
        }
    };
    for (int i = 1; i < n; i++) {
        string s, t;
        cin >> s >> t;
        s = '#' + s;
        t = '#' + t;
        upd(s, t);
    }
    vector<int> used(30, 0);
    for (int i = 1; i <= m; i++) {
        if (ans[i] != -1) {
            ++used[ans[i]];
        }
    }
    int s = m + 31, t = m + 32;
    int ss = m + 30;
    dinic.init(s, t);
    for (int i = 1; i <= m; i++) {
        if (ans[i] == -1) {
            // cerr << "fuck" << nl;
            dinic.add_edge(26 + i, t, 1);
            for (int c = 0; c < 26; c++) {
                if (!cant[i][c]) {
                    dinic.add_edge(c, 26 + i, 1);
                }
            }
        }
    }
    int las = m;
    for (int c = 0; c < 26; c++) {
        // cerr << "char: " << (char)(c + 'a') << ' ' << exact[c] << ' ' << mn_need[c] << ' ' << used[c] << ' ' << las << nl;
        if (exact[c] != -1) {
            las -= exact[c];
            int need = exact[c] - used[c];
            if (need > 0) dinic.add_edge(s, c, need);
            continue;
        }
        las -= max(mn_need[c], used[c]);
        int need = mn_need[c] - used[c];
        if (need > 0) dinic.add_edge(s, c, need);
    }
    assert(las >= 0);
    // cerr << las << nl;z`
    if (las) {
        dinic.add_edge(s, ss, las);
        for (int c = 0; c < 26; c++) {
            if (exact[c] != -1) continue;
            dinic.add_edge(ss, c, inf);
        }
    }
    int sum = dinic.max_flow();
    // cerr << sum << ' ' << accumulate(all(used), 0) << nl;
    sum = accumulate(all(used), sum);
    assert(sum == m);
    for (int c = 0; c < 26; c++) {
        for (int i = dinic.hed[c]; ~i; i = dinic.nxt[i]){
            int t = dinic.to[i];
            if (t > 26 && t < ss && dinic.las[i] == 0 && dinic.las[i ^ 1] == 1) {
                ans[t - 26] = c;
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << (char)(ans[i] + 'a');
    }
    cout << nl;
    // for (int i = 1; i <= m; i++) {
    //     cerr << ans[i] << ' ';
    // }
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