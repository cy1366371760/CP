#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define sc second
#define pb push_back
#define ll long long
#define trav(v, x) for(auto v:x)
#define VI vector<int>
#define VLL vector<ll>
//define double long double
#define all(x) (x).begin(),(x).end()
using namespace std;
const double eps = 1e-10;//1e-12
const int N = 610;
const ll mod = 998244353;//1e9 + 7;

const int dx[] = {0, 0, 1, 1, -1, -1, 2, -2, 2, -2, 2, -2};
const int dy[] = {2, -2, 2, -2, 2, -2, 0, 0, 1, 1, -1, -1};

int tot, m;
VI adj[N];
int match[N], fa[N], vis[N], pre[N];
queue<int>que;

int find(int x)
{return fa[x] == x ? x : fa[x] = find(fa[x]);}

int calc_lca(int x, int y)
{
	static int buk[N];
	static int nw;
	++nw;
	while(1)
	{
		if(x)
		{
			x = find(x);
			if(buk[x] == nw)
				return x;
			buk[x] = nw;
			x = pre[match[x]];
		}
		swap(x, y);
	}
}

void shrink(int x, int y, int lca)
{
	while(find(x) != lca)
	{
		pre[x] = y, y = match[x];
		if(vis[y] == 2)
		{
			vis[y] = 1;
			que.push(y);
		}
		if(find(x) == x)
			fa[x] = lca;
		if(find(y) == y)
			fa[y] = lca;
		x = pre[y];
	}
}

bool aug(int s)
{
	for(int i = 1; i <= tot; i++)
		fa[i] = i;
	memset(vis, 0, sizeof vis);
	memset(pre, 0, sizeof pre);
	while(!que.empty())
		que.pop();
	vis[s] = 1;
	que.push(s);
	while(!que.empty())
	{
		int nw = que.front();
		que.pop();
		trav(nxt, adj[nw])
		{
			if(find(nw) == find(nxt) || vis[nxt] == 2)
				continue;
			if(!vis[nxt])
			{
				vis[nxt] = 2;
				pre[nxt] = nw;
				if(!match[nxt])
				{
					for(int x = nxt, y; x; x = y)
					{
						y = match[pre[x]];
						match[x] = pre[x];
						match[pre[x]] = x;
					}
					return 1;
				}
				vis[match[nxt]] = 1, que.push(match[nxt]);
			}
			else
			{
				int lca = calc_lca(nw, nxt);
				shrink(nw, nxt, lca);
				shrink(nxt, nw, lca);
			}
		}
	}
	return 0;
}

void sol()
{
	// link edges!
	for(int i = 1; i <= tot; i++)
	{
		if(!match[i])
			aug(i);
	}
	//maybe output by match[]
}

