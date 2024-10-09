const int N = 1e6 + 100;
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