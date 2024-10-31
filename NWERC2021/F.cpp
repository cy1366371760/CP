#include<bits/stdc++.h>

#define nl '\n'
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
using ld = ll;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

int sgn(ld x) {
    return x < 0 ? -1 : x > 0;
}

struct Point { // 点   
    ld x, y;  
    Point() {}
    Point(ld x, ld y) : x(x), y(y) {}  
    bool operator < (Point b) const { // x第一关键字   
        return x == b.x ? y < b.y : x < b.x;  
    }  
    bool operator ==(Point b) const {  
        return !sgn(x - b.x) && !sgn(y - b.y);  
    }  
    bool operator <=(Point b) const {  
        return ((*this) < b || (*this) == b);  
    }  
    Point operator +(Point b) {  
        return Point(x + b.x, y + b.y);  
    }  
    Point operator -(Point b) {  
        return Point(x - b.x, y - b.y);  
    }  
    Point operator *(ld a) { // 标量乘   
        return Point(x * a, y * a);  
    }  
    Point operator /(ld a) { // 标量除  
        return Point(x / a, y / a);  
    }  
    ld operator *(Point b) { // 点积   
        return x * b.x + y * b.y;  
    }  
    ld operator ^(Point b) { // 叉积模长   
        return x * b.y - y * b.x;  
    }  
    Point operator -() {    // 取负,关于原点对称   
        return Point(-x, -y);  
    }  
    ld angle() {    // 反正切,与x轴方位角, (-pi, pi]    
        return atan2l(this->y, this->x);  
    }  
    ld length2() { // 视为原点到(x,y)向量，模长的平方   
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
    friend int ccw(Point a, Point b, Point c) { // c是否在(a,b)的逆时针侧   
        return sgn((b - a) ^ (c - a));  
    }  
    friend ld get_angle(Point a, Point b) { // 向量夹角   
        return acosl((a * b) / a.length() / b.length());  
    }  
    friend ld area(Point a, Point b, Point c) { //    
        return fabsl((b - a) ^ (c - a)); // (a,b)(a,c)平行四边形面积   
    }  
    friend ld get_dis2(Point a, Point b) { // 两间距离方   
        return (a - b).length2();  
    }  
    friend ld get_dis(Point a, Point b) { // 两点距离   
        return sqrtl(get_dis2(a, b));  
    }  
    friend ld project(Point a, Point b, Point c) {  // 求向量ac在向量ab上的投影长度  
        return ((b - a) * (c - a)) / (b - a).length();  
    }  
    bool up() { // 是否在一二象限内,象限的定义均为左闭右开,即第一象限[0, pi/2)   
        return y > 0 || (y == 0 && x >= 0);  
    }  
    friend ostream& operator<<(ostream& os, Point a) {  
        return os << "(" << a.x << ',' << a.y << ')';  
    }  
}; 

int fen[N + 10];
void add(int x) {
    for (; x <= N; x += x & -x) fen[x]++;
}
ll ask(int x) {
    ll res = 0;
    for (; x; x -= x & -x) res += fen[x];
    return res;
}

void solve() {
    Point s, t;
    cin >> s.x >> s.y >> t.x >> t.y;
    int n;
    cin >> n;
    vector<Point> a(n);
    ll pos = 0, neg = 0;
    vector<Point> lhs, rhs;
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        int type = ccw(s, t, a[i]);
        if (type == 0) {
            if ((t - s) * (a[i] - s) > 0) ++pos;
            else ++neg;
        } else if (type == 1) {
            lhs.pb(a[i]);
        } else {
            rhs.pb(a[i]);
        }
    }
    auto calc = [&](vector<Point> pts) {
        int n = pts.size();
        vector<int> order1(n, 0), order2(n, 0);
        iota(all(order1), 0), iota(all(order2), 0);
        memset(fen, 0, sizeof(fen));
        ll res = 0;
        sort(all(order1), [&](int a, int b) {
            auto sa = pts[a] - s;
            auto sb = pts[b] - s;
            return sgn(sa ^ sb) == 0 ? sa.length2() < sb.length2() : sgn(sa ^ sb) > 0;
        });
        sort(all(order2), [&](int a, int b) {
            auto ta = pts[a] - t;
            auto tb = pts[b] - t;
            return sgn(ta ^ tb) == 0 ? ta.length2() < tb.length2() : sgn(ta ^ tb) < 0;
        });
        vector<int> rnk(n);
        for (int i = 0; i < n; i++) {
            rnk[order2[i]] = i + 1;
        }
        for (int i : order1) {
            res += ask(rnk[i]);
            add(rnk[i]);
        }
        swap(s, t);
        return res;
    };
    cout << calc(lhs) + calc(rhs) + (pos * (pos - 1) + neg * (neg - 1)) / 2LL;
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