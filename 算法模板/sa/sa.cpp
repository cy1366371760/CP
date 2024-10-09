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

#ifdef LOCAL
void debug_out()
{
	cerr << endl;
}
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
const int inf = 1e9;
//const ll inf = 1e18;
const ll mod = 998244353;//1e9 + 7;

const int N = 2e6 + 100; // 2 * string_length!
struct SA {
	int n;
	string s;
	int m, x[N], y[N], bin[N], rnk[N], sa[N], ht[N];
	// m number of dif vals, x[i] = suf i's first dimension val
	// y[i] = who is rank i in second dimension
	void rsort() {
		for (int i = 0; i <= m; i++) bin[i] = 0;
		for (int i = 1; i <= n; i++) bin[x[i]]++;
		for (int i = 1; i <= m; i++) bin[i] += bin[i-1];
		for (int i = n; i >= 1; i--) sa[bin[x[y[i]]]--] = y[i];
	}
	void cal(int _n, string _s)
	{
		n = _n, s = _s;
		int num;
		for (int i = 0; i <= 2 * n; i++) { // remember clear!!
			x[i] = y[i] = bin[i] = rnk[i] = sa[i] = ht[i] = 0;
		}
		for(int i = 1; i <= n; i++){	
			x[i] = s[i], y[i] = i;
		}
		m = 130, rsort();
		for (int l = 1; l <= n; l <<= 1) {
			num = 0;
			for (int i = n - l + 1; i <= n; i++) y[++num] = i;
			for (int i = 1; i <= n; i++) {
				if(sa[i] > l) {
					y[++num] = sa[i] - l;
				}
			}
			rsort();
			for (int i = 0; i <= n; i++) {
				swap(x[i], y[i]);
			}
			num = x[sa[1]] = 1;
			for(int i = 2; i <= n; i++) {
				x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + l] == y[sa[i - 1] + l])? num: ++num;
			}
			if(num == n)break;
			m = num;
		}
		for (int i = 1; i <= n; i++) {
			rnk[sa[i]] = i;
		}
		int k = 0;
		for (int i = 1, j; i <= n; i++) {
			if(rnk[i] == 1) {
				ht[1] = k = 0;
				continue;
			}
			if (k) --k;
			j = sa[rnk[i] - 1];
			while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) ++k;
			ht[rnk[i]] = k;
		}
	}
} sa;


void sol()
{
	string s;
	cin >> s;
	int n = s.length();
	s = '#' + s;
	sa.cal(n, s);
	for (int i = 1; i <= n; i++) {
		cout << sa.sa[i] << ' ';
	}
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
/*
abaabccababc
5
1 2
3 4
6 6
1 9
1 3

*/
