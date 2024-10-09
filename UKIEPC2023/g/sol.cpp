#include<bits/stdc++.h>

#define ll long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define fi first
#define sc second

#define pii pair<int, int>
#define pll pair<ll, ll>
template<typename T> bool chkmin(T &a, T b){return (b < a) ? a = b, 1 : 0;}
template<typename T> bool chkmax(T &a, T b){return (b > a) ? a = b, 1 : 0;}
using namespace std;
using ld = long double;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;
  
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
    Point(T x = 0, T y = 0) : x(x), y(y) {}  
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
        return atan2l(this->y, this->x);  
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

void solve() {
    ld s, ans;
    cin >> s;
    ans = s;
    int n;
    cin >> n;
    vector<Point> node(n);
    for (int i = 0; i < n; i++) {
        cin >> node[i].x >> node[i].y;
    }
    auto get_dir_vec = [&](int i) {
        Point vec = node[i + 1] - node[i];
        return vec.unit();
    };
    auto go = [&](Point a, Point vec, ld d) {
        return a + vec * d;
    };
    auto get_need = [&](Point a, Point ed) {
        return (ed - a).length();
    };
    int l0 = 0, l1;
    Point p0 = node[0], p1;
    for (int i = 0; i < n - 1; i++) {
        ld len = get_dis(node[i], node[i + 1]);
        if (sgn(len - s) < 0) {
            s -= len;
        } else {
            l1 = i;
            p1 = go(node[i], get_dir_vec(i), s);
            break;
        }
    }
    auto doit = [&](Point a, Point b, Point va, Point vb, ld t) {
        return ((a + va * t) - (b + vb * t)).length();
    };
    while (l1 < n - 1) {
        ld tlim;
        int mov = 0;
        auto v0 = get_dir_vec(l0);
        auto v1 = get_dir_vec(l1);
        tlim = get_need(p0, node[l0 + 1]);
        if (sgn(tlim - get_need(p1, node[l1 + 1])) > 0) {
            mov = 1;
            tlim = get_need(p1, node[l1 + 1]);
        }
        chkmin(ans, doit(p0, p1, v0, v1, 0));
        chkmin(ans, doit(p0, p1, v0, v1, tlim));

        ld t;
        ld D1, D2, D3, D4;
        D1 = (p0.x - p1.x);
        D2 = (v0.x - v1.x);
        D3 = (p0.y - p1.y);
        D4 = (v0.y - v1.y);
        t = -(D1 * D2 + D3 * D4) / (D2 * D2 + D4 * D4);
        if (sgn(t) >= 0 && sgn(t - tlim) <= 0) {
            chkmin(ans, doit(p0, p1, v0, v1, t));
        }

        p0 = p0 + v0 * tlim;
        p1 = p1 + v1 * tlim;
        if (mov == 0) ++l0;
        else ++l1;
    }
    cout << fixed << setprecision(10) << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}