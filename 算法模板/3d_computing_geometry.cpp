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

const int N = 1000 + 100;
const int inf = 1e9;
//const ll inf = 1e18;
const ll mod = 998244353;//1e9 + 7;

const double eps = 1e-14, pi = acos(-1);
int sign(double x) {
	return x < -eps ? -1 : x > eps;
}
int cmp(double x, double y) {
    if (fabs(x - y) < eps)
        return 0;
    if (x < y)
        return -1;
    return 1;
}

struct Point {
    double x, y, z;
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    bool operator<(const Point& B) const {
        if (cmp(x, B.x))
            return x < B.x;
        if (cmp(y, B.y))
            return y < B.y;
        return z < B.z;
    }
    bool operator==(const Point& B) const {
        return !cmp(x, B.x) && !cmp(y, B.y) && !cmp(z, B.z);
    }
    Point operator+(const Point& B) const {
        return Point(x + B.x, y + B.y, z + B.z);
    }
    Point operator-(const Point& B) const {
        return Point(x - B.x, y - B.y, z - B.z);
    }
    Point operator*(const double a) const {
        return Point(x * a, y * a, z * a);
    }
    Point operator/(const double a) const {
        return Point(x / a, y / a, z / a);
    }
    double operator*(const Point& B) const {
        return x * B.x + y * B.y + z * B.z;
    }
    Point operator^(const Point& B) const {
        return {y * B.z - B.y * z, z * B.x - x * B.z, x * B.y - y * B.x};
    }
    double length() {
        return sqrt(x * x + y * y + z * z);
    }
    double rand_eps() {
        return ((double)rand() / RAND_MAX - 0.5) * eps;
    }
    Point trunc(double len) {
    	len /= length();
    	x *= len, y *= len, z *= len;
    	return *this;
	}
    void shake() {  // 微小扰动, 防止出现四点共面的情况
        x += rand_eps(), y += rand_eps(), z += rand_eps();
    }
};

struct Line {
	Point p, v;
	Line() {}
	Line(const Point& A, const Point& B) : p(A), v(B) {}
	Point foot_point(Point a) {     // 垂足
		return p + v * ((v * (a - p)) / (v * v));
	}
	double distance(const Point& a) {   // 点到直线的距离
		return fabs((v ^ (a - p)).length() / v.length());
	}
};

// 平面类
Point q[N];
struct Plane {
    int v[3];
    Point norm() {  // 平面法向量
        return (q[v[1]] - q[v[0]]) ^ (q[v[2]] - q[v[0]]);
    }
    double area() {  // 面积
        return norm().length() / 2;
    }
    bool above(Point a) {  // 点a是否在平面的上方
        return ((a - q[v[0]]) * norm()) >= 0;
    }
};

Plane plane[N], np[N];  // 通过微小扰动, 防止四点共面
int n, m;
bool g[N][N];           // 某条边是否是分界线
void get_convex_3d() {  // O(n^2)
    plane[m++] = {0, 1, 2}, plane[m++] = {2, 1, 0};
    for (int i = 3; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < m; j++) {
            bool t = plane[j].above(q[i]);
            if (!t)
                np[cnt++] = plane[j];
            for (int k = 0; k < 3; k++)
                g[plane[j].v[k]][plane[j].v[(k + 1) % 3]] = t;
        }
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 3; k++) {
                int a = plane[j].v[k], b = plane[j].v[(k + 1) % 3];
                if (g[a][b] && !g[b][a])
                    np[cnt++] = {a, b, i};
            }
        }
        m = cnt;
        for (int j = 0; j < m; j++)
            plane[j] = np[j];
    }
}
signed main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> q[i].x >> q[i].y >> q[i].z;
        q[i].shake();
    }
    get_convex_3d();
    double ans = 0;
    for (int i = 0; i < m; i++)
        ans += plane[i].area();
    cout << fixed << setprecision(6) << ans << endl;
}

Line planeIntersection(Point a, Point v1, Point b, Point v2) {	// 平面AB的交线 (已知平面上一点及其法向量)
	Point e = (v1 ^ v2), u = (v1 ^ e);
	double d = v2 * u;
	if (!sign(d))
		return Line(Point(0, 0), Point(0, 0));
	Point q = a + u * ((v2 * (b - a)) / d);
	return Line(q, e);
}

//经纬度转化为空间坐标
double torad(double a) {   // 角度转化为弧度
	return a / 180 * pi;
}
Point getPoint(double R, double a, double b) {  // a经度,b维度,均为角度
	a = torad(a), b = torad(b);
	return Point(R * cos(a) * cos(b), R * cos(a) * sin(b), R * sin(a));
}

//两点球面距离
double ball_dist(double R, Point a, Point b) {
	double d = (a - b).length();
	return 2 * asin(d / 2 / R) * R;
}

//直线与球交点
int lineInterBall(Line L, Point O, double R, Point& p1, Point& p2) {
	Point foot = L.foot_point(O);
	double distOF = (O - foot).length();
	if (cmp(distOF, R) > 0)
		return 0;
	else if (!cmp(distOF, R)) {
		p1 = p2 = foot;
		return 1;
	}
	Point delta = L.v.trunc(sqrt(R * R - distOF * distOF));
	p1 = foot + delta, p2 = foot - delta;
	return 2;
}
