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
#define nl '\n'
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
  
using ld = long double;  
const double eps = 1e-14;  
const double pi = acosl(-1);  
int sgn(ld x) {  
    return x < -eps ? -1 : x > eps;  
}  
int cmp(ld x, ld y) {  
    return sgn(x - y);  
}  
  
using T = ld;  
struct Point { // 点   
    T x, y;  
    int idx;
    Point(T x = 0, T y = 0) : x(x), y(y) { idx = -1;}  
    bool operator<(Point B) const{ // x第一关键字   
        return x == B.x ? y < B.y : x < B.x;  
    }  
    bool operator==(Point B) const{  
        return !sgn(x - B.x) && !sgn(y - B.y);  
    }  
    bool operator <=(Point B) const {  
        return ((*this) < B || (*this) == B);  
    }  
    Point operator+(Point B) const{  
        return Point(x + B.x, y + B.y);  
    }  
    Point operator-(Point B) const{  
        return Point(x - B.x, y - B.y);  
    }  
    Point operator*(T a) const{ // 标量乘   
        return Point(x * a, y * a);  
    }  
    Point operator/(T a) const{ // 标量除  
        return Point(x / a, y / a);  
    }  
    T operator*(Point B) const{ // 点积   
        return x * B.x + y * B.y;  
    }  
    T operator^(Point B) const{ // 叉积模长   
        return x * B.y - y * B.x;  
    }  
    Point operator-() const{    // 取负,关于原点对称   
        return Point(-x, -y);  
    }  
    ld angle() {    // 反正切,与x轴方位角, (-pi, pi]    
        ld res = atan2l(this->y, this->x);  
        if (sgn(res) < 0) {
            res += 2 * pi;
        }
        return res;
    }  
    T length2() { // 视为原点到(x,y)向量，模长的平方   
        return x * x + y * y;  
    }  
    ld length() { // 模长   
        return sqrtl(length2());  
    }  
    Point unit() {  // 单位方向向量  
        return *this / this -> length();  
    }  
    Point normal() {  // 单位法向量  
        return Point(-y, x) / this -> length();  
    }  
    Point trunc(ld r) {  // 化为长度为r的向量  
        ld l = length();  
        if (!sgn(l))  
            return *this;  
        r /= l;  
        return Point(x * r, y * r);  
    }  
    Point conj() { // 共轭向量   
        return Point(x, -y);  
    }  
    Point to_left() { // 绕原点左转90度   
        return Point(-y, x);  
    }  
    Point to_right() { // 绕原点右转90度   
        return Point(y, -x);  
    }  
    Point rotate(ld rad) {  // 逆时针旋转 rad 弧度    
        return Point(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad));  
    }  
    friend int rela(Point a, Point b, Point c) { // c是否在(a,b)的逆时针侧   
        return sgn((b - a) ^ (c - a));  
    }  
    friend ld get_angle(Point a, Point b) { // 向量夹角   
        return acosl((a * b) / a.length() / b.length());  
    }  
    friend T area(Point a, Point b, Point c) { //    
        return fabsl((b - a) ^ (c - a)); // (a,b)(a,c)平行四边形面积   
    }  
    friend T get_dis2(Point a, Point b) { // 两间距离方   
        return (a - b).length2();  
    }  
    friend ld get_dis(Point a, Point b) { // 两点距离   
        return sqrtl(get_dis2(a, b));  
    }  
    friend ld project(Point a, Point b, Point c) {  // 求向量ac在向量ab上的投影长度  
        return ((b - a) * (c - a)) / (b - a).length();  
    }  
    bool up() const { // 是否在一二象限内,象限的定义均为左闭右开,即第一象限[0, pi/2)   
        return y > 0 || (y == 0 && x >= 0);  
    }  
    friend ostream& operator<<(ostream& os, Point a) {  
        return os << "(" << a.x << ',' << a.y << ')';  
    }  
};  
  
bool argcmp(Point a, Point b) { // 关于原点极角排序,一二三四象限顺序   
    if (a.up() != b.up())  
        return a.up() > b.up();  
    return (a ^ b) == 0 ? a.x < b.x : (a ^ b) > 0;  
}  
Point rotate(Point a, Point bas, ld theta) { // a点绕bas点逆时针转theta弧度   
    return (a - bas).rotate(theta) + bas;  
}  
Point reflect(Point v, Point l) { // 光线v照射到平面l后反射  
    Point res;  
    Point E = l / l.length();  // 单位向量  
    T d = E * v;  
    return (E * 2 * d - v);  
}  
  
struct Line { // 直线   
    Point p, v; // p为直线上一点,v为方向向量   
    ld rad; // rad为方向角 (-pi, pi]   
    //亦可表示向量v逆时针方向的半平面   
    Line(){}  
    Line(Point p, Point v):p(p), v(v) {  
        rad = atan2l(v.y, v.x);  
    }  
    Point get_point(ld t) {  
        return p + v * t;  
    }  
    int under(Point a) { // 射线是否在点a下方   
        return rela(p, p + v, a);   
    }   
    bool operator <(Line b) { // 比较   
        if (!cmp(rad, b.rad)) {  
            return under(b.p) < 0; // 靠上侧的排前面  
        }  
        return rad < b.rad;  
    }  
    ld dis2point(Point a) {  // 点a到直线的距离  
        return fabsl((v ^ (a - p)) / v.length());  
    }   
    Point foot(Point a) { // 点在直线的投影点(垂足)   
        return p + v * (v * (a - p) / v.length2());  
    }  
    Point symmetry(Point a) { // 点关于直线对称的点(即镜面反射)   
        return foot(a) * 2 - a;  
    }  
    bool parallel(Line b) { // 两直线是否平行(共线也算)   
        if (!sgn(v ^ b.v)) {  
            return 1;  
        }  
        return 0;  
    }  
    bool colinear(Line b) { // 两直线是否共线   
        if (parallel(b)) {  
            if (!sgn((b.p - p) ^ v)) {  
                return 1;  
            }  
        }  
        return 0;  
    }  
    Point intersect(Line b) {  // 两直线交点(不能平行)  
        assert(!parallel(b));  
        Point u = p - b.p;  
        T t = (b.v ^ u) / (v ^ b.v);  
        return get_point(t);  
    }  
};  
  
struct Segment { // 线段   
    Point a, b;  
    Segment(){}  
    Segment(Point aa, Point bb) {  
        if (bb < aa) {  
            swap(aa, bb);  
        }  
        a = aa, b = bb;  
    }  
    bool isIntersect(Point p) { // 点p是否在线段上   
        return !sgn((a - p) ^ (b - p)) && sgn((a - p) * (b - p)) <= 0;  
    }  
    bool parallel(Segment seg) {  
        return Line(a, b - a).parallel(Line(seg.a, seg.b - seg.a));  
    }  
    bool colinear(Segment seg)  { // 两线段是否共线, 有重合部分   
        // 只考虑seg退化的情况  
        if (seg.a == seg.b) {  
            if (Line(a, b - a).under(seg.a) == 0) {  
                if (a <= seg.a && seg.a <= b) {  
                    return 1;  
                }  
            }  
            return 0;  
        }  
        if (Line(a, b - a).colinear(Line(seg.a, seg.b - seg.a))) {  
            if ((a <= seg.a && seg.a <= b) || (seg.a <= a && a <= seg.b)) {  
                return 1;  
            }  
        }  
        return 0;  
    }  
    bool isIntersect(Segment seg) { // 两线段是否相交(含端点含共线)  
        if (parallel(seg)) { //线段平行  
            return colinear(seg);  
        }  
        const Point &a1 = a, &a2 = b, &b1 = seg.a, &b2 = seg.b;  
        T c1 = (a2 - a1) ^ (b1 - a1), c2 = (a2 - a1) ^ (b2 - a1);  
        T c3 = (b2 - b1) ^ (a1 - b1), c4 = (b2 - b1) ^ (a2 - b1);  
        return sgn(c1) * sgn(c2) <= 0 && sgn(c3) * sgn(c4) <= 0;  
    }  
    bool isIntersect(Line l) { // 线段和直线是否相交 (含端点)  
        return l.under(a) * l.under(b) <= 0;  
    }  
    ld dis2point(Point p) { // 点到线段距离   
        if (sgn((p - a) * (b - a)) < 0 || sgn((p - b) * (a - b)) < 0) {  
            return min(get_dis(b, p), get_dis(a, p));   
        }  
        return Line(a, b - a).dis2point(p);  
    }  
    ld dis2seg(Segment seg) {  
        if (isIntersect(seg)) {  
            return 0;  
        }  
        return min({dis2point(seg.a), dis2point(seg.b), seg.dis2point(a), seg.dis2point(b)});  
    }  
};  
  
ld get_area(vector<Point> pts) {  
    ld res = 0;  
    for (int i = 1; i + 1 < pts.size(); i++) {  
        res += (pts[i] - pts[0]) ^ (pts[i + 1] - pts[0]);  
    }  
    return res / 2;  
}  
  
vector<Point> half_plane_intersect(vector<Line> lines) {  
    sort(all(lines));  
    deque<Point> pts;  
    deque<Line> ls;  
    for (auto l : lines) {  
        if (ls.empty()) {  
            ls.pb(l);  
            continue;  
        }  
        while(!pts.empty() && l.under(pts.back()) <= 0) {  
            pts.pop_back();  
            ls.pop_back();  
        }  
        while(!pts.empty() && l.under(pts[0]) <= 0) {  
            pts.pop_front();  
            ls.pop_front();  
        }  
        if (!sgn(ls.back().v ^ l.v)) {  
            if (sgn(ls.back().v * l.v) > 0) {  
                continue;  
            } else {  
                return vector<Point>{};  
            }  
        }  
        pts.pb(l.intersect(ls.back()));  
        ls.pb(l);  
    }  
    while(!pts.empty() && ls[0].under(pts.back()) <= 0) {  
        pts.pop_back();  
        ls.pop_back();  
    }  
    if (ls.size() > 2) {  
        pts.push_back(ls[0].intersect(ls.back()));  
    }  
    return vector<Point>(pts.begin(), pts.end());  
}  
  
vector<Line> get_half_plane(Point u, Segment v) {  
    if (((v.a - u) ^ (v.b - u)) == 0) {  
        return vector<Line>{Line(u, v.a - u), Line(v.a, u - v.a)};  
    }  
    if (((v.a - u) ^ (v.b - u)) < 0) {  
        swap(v.a, v.b);  
    }  
    return vector<Line> {  
        Line(v.a, u - v.a),  
        Line(v.a, v.b - v.a),  
        Line(u, v.b - u)  
    };  
} 

// (回转数法) 判点在多边形内外；点在多边形内返回1, 点在多边形外返回0, 点在多边形上返回-1
int point_in_polygon(const Point& p, vector<Point>& poly) {
    int wn = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        if (Segment(poly[i], poly[(i + 1) % n]).isIntersect(p))
            return -1;
        int k = sgn((poly[(i + 1) % n] - poly[i]) ^ (p - poly[i]));
        int d1 = sgn(poly[i].y - p.y);
        int d2 = sgn(poly[(i + 1) % n].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0)
            wn++;
        if (k < 0 && d2 <= 0 && d1 > 0)
            wn--;
    }
    if (wn != 0)
        return 1;
    return 0;
}

int inConvex(const Point& p, const vector<Point>& a) {   // a为凸包(按顺序排列), 1 内 0 外 -1边上 
	if (a.empty())
		return false;
	int l = 1, r = a.size() - 1;
	while (l <= r) {
		int mid = l + r >> 1;
		double ls = (a[mid] - a[0]) ^ (p - a[0]);
		double rs = (a[mid + 1] - a[0]) ^ (p - a[0]);
		if (ls >= 0 && rs <= 0) {
			int type = sgn((a[mid + 1] - a[mid]) ^ (p - a[mid]));
			if (type == 0)
				return -1;
			else if (type == 1)
				return 1;
			return 0;
		} else if (ls < 0) {
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return false;
}

struct Circle {
    Point p;
    double r;
    Circle(Point _p = Point(0, 0), double _r = 0) : p(_p), r(_r) {}
    // 三角形外接圆
    Circle(Point a, Point b, Point c) {
        Line u = Line({(a + b) / 2}, {(b - a).rotate(pi / 2)});
        Line v = Line({(a + c) / 2}, {(c - a).rotate(pi / 2)});
        p = u.intersect(v);
        r = get_dis(p, a);
    }
    // 三角形内切圆(bool t 只是为了与外接圆区别)
    Circle(Point a, Point b, Point c, bool t) {
        Line u, v;
        double m = atan2l(b.y - a.y, b.x - a.x), n = atan2l(c.y - a.y, c.x - a.x);
        u.p = a;
        u.v = u.p + Point(cos((n + m) / 2), sin((n + m) / 2));
        v.p = b;
        m = atan2l(a.y - b.y, a.x - b.x), n = atan2l(c.y - b.y, c.x - b.y);
        v.v = v.p + Point(cos((n + m) / 2), sin((n + m) / 2));
        p = u.intersect(v);
        r = Line(a, b).dis2point(p);
    }
    bool operator==(Circle v) {
        return (p == v.p) && sgn(r - v.r) == 0;
    }
    bool operator<(Circle v) const {
        return ((p < v.p) || ((p == v.p) && sgn(r - v.r) < 0));
    }
    double area() {
        return pi * r * r;
    }
    double length() {
        return 2 * pi * r;
    }
    // 点和圆的关系        -1圆内   0圆上   1圆外
    int rela(Point a) {
        double dist = get_dis(p, a);
        if (sgn(dist - r) < 0)
            return -1;
        else if (sgn(dist - r) == 0)
            return 0;
        return 1;
    }
    // 直线和圆的关系     -1相交   0相切    1相离
    int line_rela(Line v) {
        double dist = v.dis2point(p);
        if (sgn(dist - r) < 0)
            return -1;
        else if (sgn(dist - r) == 0)
            return 0;
        else
            return 1;
    }
    // 两圆的关系  5 相离   4 外切   3 相交   2内切    1 内含
    int circle_rela(Circle v) {
        double dist = get_dis(p, v.p);
        if (sgn(dist - r - v.r) > 0)
            return 5;
        if (sgn(dist - r - v.r) == 0)
            return 4;
        double l = fabs(r - v.r);
        if (sgn(dist - r - v.r) < 0 && sgn(dist - l) > 0)
            return 3;
        if (sgn(dist - l) == 0)
            return 2;
        if (sgn(dist - l) < 0)
            return 1;
        return -1;
    }
    // 求两个圆的交点，并返回交点个数
    int cross_circle(Circle v, Point& p1, Point& p2) {
        int rel = circle_rela(v);
        if (rel == 1 || rel == 5)
            return 0;
        double d = get_dis(p, v.p);
        double l = (d * d + r * r - v.r * v.r) / (d * 2);
        double h = sqrtl(r * r - l * l);
        Point tmp = p + (v.p - p).trunc(l);
        p1 = tmp + ((v.p - p).to_left().trunc(h));
        p2 = tmp + ((v.p - p).to_right().trunc(h));
        if (rel == 2 || rel == 4)
            return 1;
        return 2;
    }
    // 求直线和圆的交点，返回交点个数
    int cross_line(Line v, Point& p1, Point& p2) {
        if ((*this).line_rela(v) == 1)
            return 0;
        Point a = v.foot(p);
        double d = v.dis2point(p);
        d = sqrtl(r * r - d * d);
        if (sgn(d) == 0) {
            p1 = a, p2 = a;
            return 1;
        }
        p1 = a + v.v.trunc(d);
        p2 = a - v.v.trunc(d);
        return 2;
    }
    // 过一点作圆的切线(先判断点和圆的关系)
    int tangent_line(Point q, Line& u, Line& v) {
        int x = rela(q);
        if (x == -1)
            return 0;
        if (x == 0) {
            u = Line(q, (p - q).to_left());
            v = u;
            return 1;
        }
        double d = get_dis(p, q);
        double rad = asin(r / d);
        u = Line(q, (p - q).rotate(rad));
        v = Line(q, (p - q).rotate(-rad));
        return 2;
    }
    // 求两圆相交面积
    double circle_cross_area(Circle v) {
        int rel = circle_rela(v);
        if (rel >= 4)
            return 0;
        if (rel <= 2)
            return min(area(), v.area());
        double d = get_dis(p, v.p);
        double hf = (r + v.r + d) / 2;
        double ss = 2 * sqrtl(hf * (hf - r) * (hf - v.r) * (hf - d));
        double a1 = acos((r * r + d * d - v.r * v.r) / (2.0 * r * d));
        a1 = a1 * r * r;
        double a2 = acos((v.r * v.r + d * d - r * r) / (2.0 * v.r * d));
        a2 = a2 * v.r * v.r;
        return a1 + a2 - ss;
    }
    // 得到过a,b两点, 半径为r1的两个圆
    friend int get_circle(Point a, Point b, double r1, Circle& c1, Circle& c2) {
        Circle x(a, r1), y(b, r1);
        int t = x.cross_circle(y, c1.p, c2.p);
        if (!t)
            return 0;
        c1.r = c2.r = r1;
        return t;
    }
};

template <class T>
struct convex {
	vector<Point> q;
	convex() {}
	convex(vector<Point>& B) : q(B) {}
	convex(const convex& B) : q(B.q) {}
	convex& operator=(const convex& B) {
		q = B.q;
		return *this;
	}
	Point& operator[](int x) noexcept {
		return q[x];
	}
	int size() const {
		return q.size();
	}
	int nxt(int x) const {
		return x == size() - 1 ? 0 : x + 1;
	}
	int pre(int x) const {
		return x == 0 ? size() - 1 : x - 1;
	}
	void init(vector<Point>& v) {
		sort(v.begin(), v.end());
		int n = v.size(), top = 0;
		vector<int> st(n + 10);
		for (int i = 0; i < n; i++) {
			while (top > 1 && sgn((v[st[top]] - v[st[top - 1]]) ^ (v[i] - v[st[top - 1]])) <= 0)
				top--;
			st[++top] = i;
		}
		int k = top;
		for (int i = n - 2; i >= 0; i--) {
			while (top > k && sgn((v[st[top]] - v[st[top - 1]]) ^ (v[i] - v[st[top - 1]])) <= 0)
				top--;
			st[++top] = i;
		}
		for (int i = 1; i < top; i++)
			q.push_back(v[st[i]]);
		return;
	}
	double get_length() {
		double res = 0;
		for (int i = 0; i < size(); i++)
			res += get_dist(q[i], q[nxt(i)]);
		return res;
	}
	T get_area2() {
		T res = 0;
		for (int i = 0; i < size(); i++)
			res += (q[i] ^ q[nxt(i)]);
		return abs(res);
	}
    Point getBaryCentre() const {  // 重心
		Point res(0, 0);
		double are = 0;
		const int sz = size();
		for (int i = 1; i < sz - 1; i++) {
			double tmp = (q[i] - q[0]) ^ (q[i + 1] - q[0]);
			if (!sgn(tmp))
				continue;
			are += tmp;
			res.x += (q[0].x + q[i].x + q[i + 1].x) / 3 * tmp;
			res.y += (q[0].y + q[i].y + q[i + 1].y) / 3 * tmp;
		}
		if (sgn(are))
			res = res / are;
		return res;
	}
    vector<T> sum;
	void get_sum() {
		vector<T> a(q.size());
		for (int i = 0; i < q.size(); i++)
			a[i] = q[pre(i)] ^ q[i];
		sum.resize(q.size());
		partial_sum(a.begin(), a.end(), sum.begin());
	}
	T query_sum(int l, int r) const {
		if (l <= r)
			return sum[r] - sum[l] + (q[r] ^ q[l]);
		return sum[size() - 1] - sum[l] + sum[r] + (q[r] ^ q[l]);
	}

	// 闵可夫斯基和
	convex operator+(const convex& B) const {
		const auto& a = this->q;
		const auto& b = B.q;
		int n = q.size(), m = b.size();
		Point sa = q[0], sb = b[0];
		for (int i = 0; i < n; i++) {
			if (a[i].y < sa.y || (a[i].y == sa.y && a[i].x < sa.x))
				sa = a[i];
		}
		for (int i = 0; i < m; i++) {
			if (b[i].y < sb.y || (b[i].y == sb.y && b[i].x < sb.x)) {
				sb = b[i];
			}
		}
		auto s = sa + sb;
		vector<Point> d(n + m);
		for (int i = 0; i < n; i++)
			d[i] = a[(i + 1) % n] - a[i];
		for (int i = 0; i < m; i++)
			d[n + i] = b[(i + 1) % m] - b[i];
		sort(d.begin(), d.end(), [&](const Point& A, const Point& B) {
			if (A.up() ^ B.up())
				return A.up() > B.up();
			return (A ^ B) > 0;
		});
		vector<Point> c(n + m);
		c[0] = s;
		for (int i = 0; i < n + m - 1; i++)
			c[i + 1] = c[i] + d[i];
		convex res;
		res.init(c);
		return res;
	}

	// 旋转卡壳
	template <class F>
	void rotating_calipres(const F& func) const {
		for (int i = 0, j = 1; i < q.size(); i++) {
			auto d = q[i], e = q[nxt(i)];
			func(d, e, q[j]);
			while (area(d, e, q[j]) <= area(d, e, q[nxt(j)])) {
				j = nxt(j);
				func(d, e, q[j]);
			}
		}
	}

	// 凸包直径(平方)
	T diameter2() const {
		if (q.size() == 1)
			return 0;
		if (q.size() == 2)
			return get_dis2(q[0], q[1]);
		T ans = 0;
		auto func = [&](const Point& a, const Point& b, const Point& c) {
			ans = max({ans, get_dis2(a, c), get_dis2(b, c)});
		};
		rotating_calipres(func);
		return ans;
	}

	// 凸多边形关于某一方向的极点, 复杂度 O(logn)
	template <class F>
	int extreme(const F& dir) const {
		const auto check = [&](const int i) {
			return sgn(dir(q[i]) ^ (q[nxt(i)] - q[i])) >= 0;
		};
		const auto dir0 = dir(q[0]);
		const auto check0 = check(0);
		if (!check0 && check(this->size() - 1))
			return 0;
		const auto cmp = [&](const Point& v) {
			const int vi = &v - q.data();
			if (vi == 0)
				return 1;
			const auto checkv = check(vi);
			const auto t = sgn(dir0 ^ (v - q[0]));
			if (vi == 1 && checkv == check0 && sgn(dir0 ^ (v - q[0])) == 0)
				return 1;
			return checkv ^ (checkv == check0 && t <= 0);
		};
		return partition_point(q.begin(), q.end(), cmp) - q.begin();
	}

	// 过凸多边形外一点求凸多边形的切线, 返回切点下标, 复杂度 O(logn)
	// 必须保证点在多边形外
	pair<int, int> tangent(const Point& a) const {
		const int i = extreme([&](const Point& u) {
			return u - a;
		});
		const int j = extreme([&](const Point& u) {
			return a - u;
		});
		return {i, j};
	}

	// 求平行于给定直线的凸多边形的切线, 返回切点下标, 复杂度 O(logn)
	pair<int, int> tangent(const Line& a) const {
		const int i = extreme([&](...) {
			return a.v;
		});
		const int j = extreme([&](...) {
			return -a.v;
		});
		return {i, j};
	}
	
	friend int inConvex(const Point& p, const convex& c) {
		return inConvex(p, c.q);
	}
};
using Convex = convex<ld>;

using _T = ld;
pair<_T, _T> minmax_triangle(const vector<Point>& vec) { //最小最大三角形面积
	if (vec.size() <= 2)
		return {0, 0};
	const _T tmpans = abs((vec[0] - vec[1]) ^ (vec[0] - vec[2]));
	_T maxans = tmpans, minans = tmpans;

	vector<pair<int, int>> evt;
	evt.reserve(vec.size() * vec.size());

	for (signed i = 0; i < vec.size(); i++) {
		for (signed j = 0; j < vec.size(); j++) {
			if (i == j || vec[i] == vec[j])
				continue;
			evt.push_back({i, j});
		}
	}
	sort(evt.begin(), evt.end(), [&](const pair<int, int>& u, const pair<int, int>& v) {
		const Point du = vec[u.second] - vec[u.first], dv = vec[v.second] - vec[v.first];
		return argcmp({du.y, -du.x}, {dv.y, -dv.x});
	});
	vector<signed> vx(vec.size()), pos(vec.size());
	for (signed i = 0; i < vec.size(); i++)
		vx[i] = i;
	sort(vx.begin(), vx.end(), [&](int x, int y) {
		return vec[x] < vec[y];
	});
	for (signed i = 0; i < vx.size(); i++)
		pos[vx[i]] = i;
	for (auto [u, v] : evt) {
		signed i = pos[u], j = pos[v];
		if (i > j)
			swap(u, v), swap(i, j);
		const Point vecu = vec[u], vecv = vec[v];
		if (i > 0)
			minans = min(minans, abs((vec[vx[i - 1]] - vecu) ^ (vec[vx[i - 1]] - vecv)));
		if (j < vx.size() - 1)
			minans = min(minans, abs((vec[vx[j + 1]] - vecu) ^ (vec[vx[j + 1]] - vecv)));
		maxans = max({maxans, abs((vec[vx[0]] - vecu) ^ (vec[vx[0]] - vecv)), abs((vec[vx.back()] - vecu) ^ (vec[vx.back()] - vecv))});
		swap(vx[i], vx[j]);
		pos[u] = j, pos[v] = i;
	}
	return {minans, maxans};
}

/* 动态凸包 1.插入一个点   2.查询某个点是否被凸包包含(包括边界) */
struct Hull {
	set<Point> su, sd;
	bool query(set<Point>& s, Point u, int flag) {
		auto l = s.upper_bound(u), r = s.lower_bound(u);
		if (r == s.end() || l == s.begin())
			return false;
		l--;
		return rela(*l, u, *r) * flag >= 0;
	}
	void insert(set<Point>& s, Point u, int flag) {
		if (query(s, u, flag))
			return;
		auto it = s.insert(u).first;
		while (true) {
			auto mid = it;
			if (mid == s.begin())
				break;
			auto l = --mid;
			if (l == s.begin())
				break;
			l--;
			if (rela(*l, *mid, u) * flag <= 0)
				break;
			s.erase(mid);
		}
		while (true) {
			auto mid = it;
			mid++;
			if (mid == s.end())
				break;
			auto r = mid;
			r++;
			if (r == s.end())
				break;
			if (rela(u, *mid, *r) * flag <= 0)
				break;
			s.erase(mid);
		}
	}
	void insert(Point u) {
		insert(su, u, 1), insert(sd, u, -1);
	}
	int check(Point u) {
		return query(su, u, 1) && query(sd, u, -1);
	}
};

void sol() {
	int n;
    ld las;
    cin >> n >> las;
    vector<Point> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].idx = i;
    }
    sort(a.begin() + 1, a.begin() + n + 1, [&](Point u, Point v) {
        return sgn(u.angle() - v.angle()) == 0 ? u.length() < v.length() : u.angle() < v.angle();
    });
    a[0] = Point(0, 0);
    // for (int i = 0; i <= n; i++) {
    //     cerr << a[i] << ' ' << a[i].angle() << nl;
    // } cerr << nl;
    auto v = a;
    int top = 0;
    vector<int> st(n + 10);
    for (int i = 0; i <= n; i++) {
        while (top > 1 && sgn((v[st[top]] - v[st[top - 1]]) ^ (v[i] - v[st[top - 1]])) <= 0)
            top--;
        st[++top] = i;
    }
    int bf = -1;
    for (int i = 1; i < top; i++) {
        ld nw = (v[st[i]] - v[st[i + 1]]).length();
        // cerr << "GG" << v[st[i]] << ' ' << v[st[i]].idx << nl;
        if (sgn(las - nw) < 0) {
            cout << bf << nl;
            return;
        }
        las -= nw;
        bf = v[st[i + 1]].idx;
    }
    vector<Point> convex;
    convex.pb(v[st[top]]);
    for (int i = 2; i < top; i++) {
        convex.pb(v[st[i]]);
    }
    {
        int top = 0;
        auto v = convex;
        int n = v.size();
        vector<int> st(n + 10);
        for (int i = 0; i < n; i++) {
            while (top > 1 && sgn((v[st[top]] - v[st[top - 1]]) ^ (v[i] - v[st[top - 1]])) <= 0)
                top--;
            st[++top] = i;
        }
        convex.clear();
        for (int i = 1; i <= top; i++) {
            convex.pb(v[st[i]]);
        }
        // if (!flg) break;
        // cerr << flg << nl;
        // for (auto p : convex) cerr << p << ' ';
        // cerr << nl;
        // for (int i = 0; i < convex.size(); i++) {
        //     ld nw = (convex[(i + 1) % convex.size()] - convex[i]).length();
        //     if (sgn(las - nw) < 0) {
        //         cout << bf << nl;
        //         return;
        //     }
        //     las -= nw;
        //     bf = convex[(i + 1) % convex.size()].idx;
        // }
    }
    ld sum = 0;
    for (int i = 0; i < convex.size(); i++) {
        sum += (convex[(i + 1) % convex.size()] - convex[i]).length();
    }
    ll kill = floor(las / sum);
    las -= kill * sum;
    for (int i = 0; i < convex.size(); i++) {
        ld nw = (convex[(i + 1) % convex.size()] - convex[i]).length();
        if (sgn(las - nw) < 0) {
            cout << bf << nl;
            return;
        }
        las -= nw;
        bf = convex[(i + 1) % convex.size()].idx;
    }
    assert(0);
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
