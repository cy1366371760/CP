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
		ed[ps] = id;
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
		for (int i = 0; i < n; i++) {
			int nw = s[i] - 'a';
			while (ps && !nxt[ps][nw]) ps = fail[ps];
			ps = nxt[ps][nw];
			++vis[ps];
		}
	}
	void sol() {
		
	}
}aho;
// usage: aho.init() aho.ins(), aho.build()