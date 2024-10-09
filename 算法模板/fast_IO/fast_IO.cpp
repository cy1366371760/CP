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

namespace IO 
{
char buf[1 << 20], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
inline int rd()
{
	int x = 0, f = 1;
	char c = gc();
	while (!isdigit(c)) 
	{
		if (c == '-')
			f = -1;
    	c = gc();
	}
	while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
	return x * f;
}
char pbuf[1 << 20], *pp = pbuf;
inline void push(const char &c)
{
	if (pp - pbuf == 1 << 20) fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf;
	*pp++ = c;
}
inline void write(int x)
{
	static int sta[35];
	int top = 0;
	do 
	{
		sta[top++] = x % 10, x /= 10;
	} while (x);
	while (top) push(sta[--top] + '0');
}
inline void outall()
{
	if(pp - pbuf)
		fwrite(pbuf, 1, pp - pbuf, stdout);
}
}  // namespace IO

using namespace IO;

void sol()
{
	int x;
	x = rd();
	write(x);
	outall();
}

signed main()
{
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
		
//	ios::sync_with_stdio(0);
//	cin.tie(0);
//	int tt;
//	cin >> tt;
//	while(tt--)
		sol();
}


