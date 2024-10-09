//#define LOCAL
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define sc second
#define pb push_back
#define ll long long
#define trav(v,x) for(auto v:x)
#define all(x) (x).begin(), (x).end()
#define VI vector<int>
#define VLL vector<ll>
#define pll pair<ll, ll>
#define double long double
//#define int long long
using namespace std;
const int N = 1e6 + 100;
const int inf = 1e9;
//const ll inf = 1e18
const ll mod = 998244353;//1e9 + 7

#ifdef LOCAL
void debug_out(){cerr << endl;}
template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
	cerr << " " << to_string(H);
	debug_out(T...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

struct Line {
	ll k, b;
	ll operator () (ll x)
	{
		return k * x + b;
	}
	Line (){};
	Line (ll k, ll b):k(k), b(b){};
};

const int m = 2e5 + 100;
struct lc_tree {
	#define mid ((l + r) >> 1)
	#define ls (k << 1)
	#define rs (k << 1 | 1)
	Line seg[m + m + 100];
	bool hav[m + m + 100];
	VI bin;
	
	void ins(Line x, int L, int R, int l = 1, int r = m, int k = 1)
	{
		if(l > R || r < L)
			return;
		if(L <= l && r <= R)
		{
			if(!hav[k])
				return (void)(hav[k] = 1, seg[k] = x, bin.pb(k));
			if(seg[k](mid) > x(mid))
				swap(seg[k], x);
			if(x(l) < seg[k](l))
				ins(x, L, R, l, mid, ls);
			if(x(r) < seg[k](r))
				ins(x, L, R, mid + 1, r, rs);
			return;
		}
		ins(x, L, R, l, mid, ls);
		ins(x, L, R, mid + 1, rs);
		return;
	}
	ll ask(ll x, int l = 1, int r = m, int k = 1)
	{
		if(!hav[k])
			return 1e18;
		if(l == r)
			return seg[k](x);
		if(x <= mid)
			return min(seg[k](x), ask(x, l, mid, ls));
		else
			return min(seg[k](x), ask(x, mid + 1, r, rs));
	}
	void init()
	{
		memset(hav, 0, sizeof hav);
		bin.clear();
	}
	void clear()
	{
		trav(v, bin)
			hav[v] = 0;
		bin.clear();
	}
}lc;

int n;
ll a[N];
VI adj[N];

int rt, tot, sz[N], mn_sz;
bool vis[N];

void dfs(int x, int ff)
{
	int mx = 0;
	sz[x] = 1;
	trav(v, adj[x])
	{
		if(vis[v] || v == ff)
			continue;
		dfs(v, x);
		mx = max(mx, sz[v]);
		sz[x] += sz[v];
	}
	mx = max(mx, tot - sz[x]);
	if(mx < mn_sz)
		rt = x, mn_sz = mx;
}

void find_rt(int x)
{
	rt = x;
	mn_sz = 1e9;
	dfs(x, 0);
}

VI buk;
ll dis[N], ans[N];

void work(int x, int dd, int ff)
{
	buk.pb(x);
	dis[x] = dd;
	trav(v, adj[x])
	{
		if(vis[v] || v == ff)
			continue;
		work(v, dd + 1, x);
	}
}

void sol(int x)
{
	lc.clear();
	buk.clear();
	vis[x] = 1;
	work(x, 0, 0);
	sort(all(buk), [](int x, int y)
	{
		return a[x] < a[y];
	});
	for(int lp = 0, rp; lp < buk.size(); lp = rp + 1)
	{
		rp = lp;
		while(a[buk[lp]] == a[buk[rp]] && rp < buk.size()) ++rp;
		--rp;
		for(int i = lp; i <= rp; i++)
		{
			int v = buk[i];
			ans[v] = min(ans[v], lc.ask(dis[v] + 1));
		}
		for(int i = lp; i <= rp; i++)
		{
			int v = buk[i];
			lc.ins(Line(a[v], dis[v] * a[v]), 1, m);
		}
	}
	trav(v, adj[x])
	{
		if(vis[v])
			continue;
		tot = sz[v], find_rt(v);
		sol(rt);
	}
}

void mian()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for(int i = 1; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	lc.init();
	memset(ans, 63, sizeof ans);
	tot = n;
	find_rt(n);
	sol(rt);
	ll res = 0;
	for(int i = 1; i <= n; i++)
	{
		if(ans[i] >= 1e18)
			continue;
		//cerr << ans[i] << '\n';
		res += ans[i] + a[i];
	}
	cout << res << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	mian();
}

