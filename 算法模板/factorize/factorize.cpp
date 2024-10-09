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
#define int long long
using namespace std;
const int N = 1e6 + 100;
const int inf = 1e9;
//const ll inf = 1e18;
const ll mod = 1e9 + 7;

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

ll qpow(ll x, ll y)
{
	ll res = 1;
	while(y)
	{
		if(y & 1)
			res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}


namespace dec
{
	ll pri[N];
	int pnum;
	bool np[N];
	void init()
	{
		int n = 1e6;
		for(int i = 2; i <= n; i++)
		{
			if(!np[i])
				pri[++pnum] = i;
			for(int j = 1; j <= pnum && i * pri[j] <= n; j++)
			{
				np[i * pri[j]] = 1;
				if(i % pri[j] == 0)
					break;
			}
		}
	}
	
	ll val[40], cnt[40], cc, cur;
	VLL buk;
	void dfs(int x)
	{
		if(x > cc)
		{
			//cerr << cur << '\n';
			buk.pb(cur);
			return;
		}
		dfs(x + 1);
		int bf = cur;
		for(int i = 1; i <= cnt[x]; i++)
		{
			cur *= val[x];
			dfs(x + 1);
		}
		cur = bf;
	}
	VLL work(ll nw)
	{
		cc = 0, buk.clear();
		for(int i = 1; i <= pnum && pri[i] <= nw / pri[i]; i++)
		{
			if(nw % pri[i])
				continue;
			val[++cc] = pri[i];
			cnt[cc] = 0;
			while(nw % pri[i] == 0)
				++cnt[cc], nw /= pri[i];
		}
		if(nw > 1)
			val[++cc] = nw, cnt[cc] = 1;
		cur = 1, dfs(1);
		sort(all(buk));
		return buk;
	}
}

void sol()
{
	ll n, m;
	cin >> n;
	dec::init();
	VLL res = dec::work(n);
	trav(v, res)
		cerr << v << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
//	int tt;
//	cin >> tt;
//	while(tt--)
		sol();
}


