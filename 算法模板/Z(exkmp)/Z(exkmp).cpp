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
#define nl '\n'
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

/*
	For multiple strings
	Consider concatenate them
	Then use Z_algo
	Get Z arrays
	Z[i] indicates LCP of s[i...] and s[0...]
	Notice s starts from index 0
*/ 
vector<int> Z_algo(string s) {
	int n = s.length();
	vector<int> Z(n, 0);
	int lp = 0, rp = 0;
	for(int i = 1; i < n; i++) {
		if(i <= rp && i + Z[i - lp] - 1 < rp) {
			Z[i] = Z[i - lp];
		} else {
			int k = max(0, rp - i + 1);
			while(i + k < n && s[k] == s[i + k]) {
				++k;
			}
			Z[i] = k;
		}
		if(i + Z[i] - 1 > rp) {
			lp = i, rp = i + Z[i] - 1;
		}
	}
	Z[0] = n;
	return Z;
}

void sol()
{
	string s, t;
	cin >> t >> s;
	int n = s.length();
	int m = t.length();
	s += t;
	auto Z = Z_algo(s);
	ll res = 0;
	for (int i = 0; i < n; i++) {
		res ^= 1LL * (i + 1) * (min(Z[i], n - i) + 1);
	}
	cout << res << nl;
	res = 0;
	for (int i = n; i < n + m; i++) {
		res ^= 1LL * (i - n + 1) * (Z[i] + 1);
	}
	cout << res << nl;
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

