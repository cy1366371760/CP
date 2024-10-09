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
//#define int long long
using namespace std;
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

const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;//1e9 + 7;

#define db long double
using pt = std::complex<db>;
#define x real
#define y imag
const db eps = 1e-12;
const db pi = acos(-1);
int sgn(db x)
{return x < -eps ? -1 : x > eps;}
db sqr(db x)
{return x * x;}
db dot(const pt &a, const pt &b)
{
	return (conj(a) * b).x();
}
db cross(const pt &a, const pt &b)
{
	return (conj(a) * b).y();
}
db cross(const pt &p, const pt &a, const pt &b)
{
	return cross(a - p, b - p);
}
db cal_len(const pt &a)
{
	return sqrt(dot(a, a));
}
db dis(const pt &a, const pt &b)
{
	return cal_len(a - b);
}
pt turn(const pt &a, double ang) // clockwise, ang is rad (such as pi / 4)
{
	return (pt){a.x() * cos(ang) + a.y() * sin(ang), -a.x() * sin(ang) + a.y() * cos(ang)};
}
pt insec(const pt &a, const pt &b, const pt &c, const pt &d) // insec of segment(a, b) and segment(c, d) 
{
	return a + (b - a) * cross(c - a, d - a) / cross(b - a, d - c);
}
pt reflect(const pt &p, const pt &a, const pt &b) // p reflects by the line(a, b)
{
	return a + conj((p - a) / (b - a)) * (b - a);
}
pt foot(const pt &p, const pt &a, const pt &b) // p's projection on line(a, b)
{
	return (p + reflect(p, a, b)) / pt(2, 0);
}
bool onseg(const pt &p, const pt &a, const pt &b) // check if p is on segment(a, b)
{
	return sgn(cross(a, b, p)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}
db rad(const pt &a)// 相对x正半轴方位角大小，单位rad 
{return atan2l(a.y(), a.x());}
ostream &operator<<(ostream &os, const pt &p)
{
	return os << "(" << p.x() << "," << p.y() << ")";
}
void sol()
{
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



