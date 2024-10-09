const int N = 1e6 + 100;
struct Mcmf {
	int s, t;
	bool inq[N];
	int pre[N], dis[N], hed[N], nxt[N], las[N], to[N], cost[N], cnt;
	bool spfa()  
	{  
	    memset(inq, 0, (t + 5) * sizeof (int)); 
	    memset(pre, -1, (t + 5) * sizeof (int)); 
	    memset(dis, 127, (t + 5) * sizeof (int));
		vector<int> que;
		dis[s] = 0, inq[s] = 1, que.pb(s);
		for (int q = 0; q < que.size(); q++) {
			int nw = que[q];
			inq[nw] = 0;
			for (int i = hed[nw]; ~i; i = nxt[i]) {
				int v = to[i];
				if (las[i] && dis[v] > dis[nw] + cost[i]) {
					dis[v] = dis[nw] + cost[i];
					pre[v] = i;
					if (!inq[v]) {
						que.pb(v);
						inq[v] = 1;
					}
				}
			}
		}
	    return dis[t] <= (int)1e9;  
	}  
	pair<ll, ll> mcmf()  
	{  
	    ll flow = 0, nw = 0, spd = 0;  
	    while(spfa())  
	    {  
	        nw = 1e9;  
	        for (int i = pre[t]; ~i; i = pre[to[i ^ 1]]) {
				nw = min(nw, las[i]);	
			}
			for (int i = pre[t]; ~i; i = pre[to[i ^ 1]]) {
				las[i] -= nw;
				las[i ^ 1] += nw;
			} 
	        flow += nw, spd += nw * dis[t];  
	    }  
	    return make_pair(flow, spd);
	}
	void init(int _s, int _t)
	{
	    memset(nxt,-1,sizeof nxt);
	    memset(hed,-1,sizeof hed);
	    cnt = -1;
	    s = _s, t = _t;
	    return;
	}
	void add_edge(int u,int v,int w, int c)//加边
	{
	    nxt[++cnt] = hed[u], las[cnt] = w, to[cnt] = v, hed[u] = cnt, cost[cnt] = c;
	    nxt[++cnt] = hed[v], las[cnt] = 0, to[cnt] = u, hed[v] = cnt, cost[cnt] = -c;
	}
};