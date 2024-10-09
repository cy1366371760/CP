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
//const ll inf = 1e18;
const ll mod = 998244353;//1e9 + 7;

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

void sol()
{
	string s, t;
	cin >> t >> s;
	int n, m;
	n = s.length();
	m = t.length();
	VI Z(n, 0);
	int lp, rp;
	lp = rp = 0;
	for(int i = 1; i < n; i++)
	{
		if(i <= rp && i + Z[i - lp] - 1 < rp)
			Z[i] = Z[i - lp];
		else
		{
			int k = max(0, rp - i + 1);
			while(i + k < n && s[k] == s[i + k])
				++k;
			Z[i] = k;
		}
		if(i + Z[i] - 1 > rp)
			lp = i, rp = i + Z[i] - 1;
	}
	Z[0] = n;
	ll res = 0;
	for(int i = 0; i < n; i++)
		res ^= 1LL * (i + 1) * (Z[i] + 1);
	cout << res << '\n';
	res = 0;
	lp = rp = -1;
	VI ans(m, 0);
	for(int i = 0; i < m; i++)
	{
		if(i <= rp && i + Z[i - lp] - 1 < rp)
			ans[i] = Z[i - lp];
		else
		{
			int k = max(0, rp - i + 1);
			while(i + k < m && k < n && s[k] == t[i + k])
				++k;
			ans[i] = k;
		}
		if(i + ans[i] - 1 > rp)
			lp = i, rp = i + ans[i] - 1;
		res ^= 1LL * (i + 1) * (ans[i] + 1);
	}
	cout << res << '\n';
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

