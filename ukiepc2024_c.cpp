#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define sc second
#define pb push_back
#define eb emplace_back
#define nl '\n'
#define all(x) (x).begin(),(x).end()
using namespace std;
using ld = long double;
template<class T> bool chkmin(T &x, T y) {if (x > y) {x = y;return 1;}return 0;}
template<class T> bool chkmax(T &x, T y) {if (x < y) {x = y;return 1;}return 0;}

const ld EPS = 1e-14;
const ld inf = 1e18;


int sgn(ld x) {
    return x < -EPS ? -1 : x > EPS;
}

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0): x(x), y(y) {}

    bool operator<(Point B) const {
        return x == B.x ? y < B.y : x < B.x;
    }
    bool operator==(Point B) const {
        return !sgn(x - B.x) && !sgn(y - B.y);
    }
    bool operator<=(Point B) const {
        return ((*this) < B) || ((*this) == B);
    }


    Point operator+(Point B) const {
        return Point(x + B.x, y + B.y);
    }

    Point operator-(Point B) const {
        return Point(x - B.x, y - B.y);
    }
    Point operator *(ld a) const {
        return Point(x * a, y * a);
    }
    ld operator *(Point B) const {
        return x * B.x + y * B.y;
    }
    ld operator^(Point B) const {
        return x*B.y - y*B.x;
    }
    ld length2() {
        return x * x + y * y;
    }
    ld length() {
        return sqrtl(length2());
    }

    friend int rela(Point a, Point b, Point c) {
        return sgn((b-a) ^ (c-a));
    }
};

struct Line {
    Point p, v;
    ld rad;
    Line(Point p, Point v): p(p), v(v) {
        rad = atan2l(v.y, v.x);
    }
    Point get_point(ld t) {
        return p + v * t;
    }
    bool parallel(Line b) {
        if (!sgn(v ^ b.v)) {
            return 1;
        }
        return 0;
    }

    int under(Point a) {
        return rela(p, p+v, a);
    }

    bool colinear(Line b) {
        if (parallel(b)) {
            if (!sgn((b.p - p) ^ v)) {
                return 1;
            }
        }
        return 0;
    }
    Point foot(Point a) {
        return p + v * (v * (a - p) / v.length2());
    }
    Point symmetry(Point a) {
        return foot(a) + foot(a) - a;
    }
    Point intersect(Line b) {
        assert(!parallel(b));
        Point u = p - b.p;
        ld t = (b.v ^ u) / (v ^ b.v);
        return get_point(t);
    }
};

struct Segment {
    Point a, b;
    Segment(){}
    Segment(Point aa, Point bb) {
        if (bb < aa) {
            swap(bb, aa);
        }

        a = aa; b = bb;
    }

    bool parallel(Segment seg) {
        return Line(a,b-a).parallel(Line(seg.a, seg.b - seg.a));
    }

    bool colinear(Segment seg) {
        if (seg.a == seg.b) {
            if (Line(a, b-a).under(seg.a) == 0) {
                if (a <= seg.a && seg.a <= b) {
                    return 1;
                }
            }
            return 0;
        }

        if (Line(a, b-1).colinear(Line(seg.a, seg.b-seg.a))) {
            if ((a <= seg.a && seg.a <= b) || (seg.a <= a && a <= seg.b)) {
                return 1;
            }
        }
        return 0;
    }

    bool is_intersect(Segment seg) {
        if (parallel(seg)) {
            return colinear(seg);
        }
        const Point &a1 = a, &a2 = b, &b1 = seg.a, &b2 = seg.b;
        ld c1 = (a2 - a1) ^ (b1 - a1);
        ld c2 = (a2 - a1) ^ (b2 - a1);
        ld c3 = (b2 - b1) ^ (a1 - b1);
        ld c4 = (b2 - b1) ^ (a2 - b1);
        return sgn(c1) * sgn(c2) <= 0 && sgn(c3) * sgn(c4) <= 0;
    }
};


vector<Point> shape1, shape2;


inline double get_area(vector<Point> pts) {
    ld res = 0;
    for (int i=1;i+1<pts.size();i++) {
        res += (pts[i] - pts[0]) ^ (pts[i+1] - pts[0]);
    }

    return fabsl(res)/2.0;
}



inline bool intersect_shape(ld scale) {
    vector<Point> shape3;
    for (auto p : shape1) {
        shape3.pb(Point(p.x * scale, p.y * scale));
    }
    if (get_area(shape3) >= get_area(shape2)) return true;
    for (int i=0;i<shape3.size();i++) for (int j=0;j<shape2.size();j++) {
        auto s1 = Segment(shape3[i], shape3[(i+1)%shape3.size()]);
        auto s2 = Segment(shape2[j], shape2[(j+1)%shape2.size()]);
        if (s1.is_intersect(s2))
            return true;
    }
    
    return false;
}


void solve() {
    int n; 
    cin >> n;
    Point bg;
    cin >> bg.x >> bg.y;
    vector<Segment> seg(n);
    vector<Point> maybe;
    maybe.pb(bg);
    for (int i = 0; i < n; i++) {
        Point u, v;
        cin >> u.x >> u.y;
        cin >> v.x >> v.y;
        seg[i] = Segment(u, v);
        maybe.pb(u);
        maybe.pb(v);
    }
    Point ed;
    cin >> ed.x >> ed.y;
    maybe.pb(ed);
    int sz = maybe.size();
    vector dp(1 << n, vector<ld> (sz, 1e18));
    dp[0][0] = 0;
    int lim = (1 << n) - 1;
    for (int sta = 0; sta < lim; sta++) {
        for (int ps = 0; ps < sz; ps++) {
            if (dp[sta][ps] < inf - EPS) {
                Point nw = maybe[ps];
                int need = 0;
                while (sta >> need & 1) ++need;
                for (int nx = 0; nx < sz; nx++) {
                    Segment cur = Segment(nw, maybe[nx]);
                    int gain = 0;
                    int st = need;
                    Segment fir = cur;
                    for (int l = st; l < n; l++) {
                        if (fir.is_intersect(seg[l])) {
                            gain |= (1 << l);
                        } else {
                            st = l;
                            break;
                        }
                    }
                    // if (gain == 0) continue;
                    chkmin(dp[sta | gain][nx], dp[sta][ps] + (nw - maybe[nx]).length());
                }



                for (int chk = 0; chk < n; chk++) {
                    Segment chkp = seg[chk];
                    Line chkp_line = Line(chkp.a, chkp.b - chkp.a);
                    Point rec_nw = chkp_line.symmetry(nw);
                    // cerr << chk << ' ';
                    // cerr << "!!" << nw.x << ',' << nw.y << ' ' << rec_nw.x << ',' << rec_nw.y << nl;
                    for (int nx = 0; nx < sz; nx++) {
                        Segment cur = Segment(rec_nw, maybe[nx]);
                        if (!cur.is_intersect(chkp)) {
                            continue;
                        }
                        Point md = chkp_line.intersect(Line(cur.a, cur.b - cur.a));
                        int gain = 0;
                        int st = need;
                        Segment fir = Segment(nw, md);
                        Segment sec = Segment(md, maybe[nx]);
                        for (int l = st; l < n; l++) {
                            if (l == chk || fir.is_intersect(seg[l])) {
                                gain |= (1 << l);
                            } else {
                                st = l;
                                break;
                            }
                        }
                        for (int l = st; l < n; l++) {
                            if (l == chk || sec.is_intersect(seg[l])) {
                                gain |= (1 << l);
                            } else {
                                st = l;
                                break;
                            }
                        }
                        // if (gain == 0) continue;
                        chkmin(dp[sta][nx], dp[sta][ps] + (rec_nw - maybe[nx]).length());
                    }
                }
            }
        }
    }
    cout << fixed << setprecision(12) << dp[lim][sz - 1] << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}