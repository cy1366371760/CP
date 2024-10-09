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


#define double long double
const double eps = 1e-12;  
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
    friend int relation(Point a, Point b, Point c) { // c是否在(a,b)的逆时针侧   
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

struct Circle {
    Point p;
    double r;
    Circle(Point _p = Point(0, 0), double _r = 0) : p(_p), r(_r) {}
    // 三角形外接圆
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
    int relation(Point a) {
        double dist = get_dis(p, a);
        if (sgn(dist - r) < 0)
            return -1;
        else if (sgn(dist - r) == 0)
            return 0;
        return 1;
    }
    // 两圆的关系  5 相离   4 外切   3 相交   2内切    1 内含
    int circle_relation(Circle v) {
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
        int rel = circle_relation(v);
        if (rel == 1 || rel == 5)
            return 0;
        ld d = get_dis(p, v.p);
        ld l = (d * d + r * r - v.r * v.r) / (d * 2);
        ld h = sqrtl(r * r - l * l);
        Point tmp = p + (v.p - p).trunc(l);
        p1 = tmp + ((v.p - p).to_left().trunc(h));
        p2 = tmp + ((v.p - p).to_right().trunc(h));
        if (rel == 2 || rel == 4)
            return 1;
        return 2;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<array<ll, 3>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }

    ld l = 0, r = 1e7, res = 1e7;
    for (int ttt = 0; ttt <= 50; ttt++) {
        ld mid = (l + r) / 2.0;
        // mid = 2.4;
        vector<Point> chk_list;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                Point p = Point(a[i][0], a[i][1]);
                Point q = Point(a[j][0], a[j][1]);
                Circle cp = Circle(p, mid / a[i][2]);
                Circle cq = Circle(q, mid / a[j][2]);
                Point m1, m2;
                int cm = cp.cross_circle(cq, m1, m2);
                // cerr << "FFF" << i << ' ' << j << ' ' << cm << '\n';
                if (cm >= 1) {
                    chk_list.pb(m1);
                }
                if (cm >= 2) {
                    chk_list.pb(m2);
                }
            }
            chk_list.pb(Point(a[i][0], a[i][1]));
        }
        ld need = 1e18;
        for (auto p : chk_list) {
            // cerr << "??" << t << '\n';
            // cerr << p << '\n';
            vector<ld> needs;
            for (int i = 0; i < n; i++) {
                Point q = Point(a[i][0], a[i][1]);
                needs.pb(get_dis(p, q) / ((ld)1.0 / a[i][2]));
            }
            sort(all(needs));
            chkmin(need, needs[k - 1]);
            // cerr << p << " ff: " << needs[k - 1] << '\n';
        }
        if (need - eps <= mid) res = mid, r = mid;
        else l = mid; 
    }
    cout << res << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(10);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
        solve();
    return 0;
}