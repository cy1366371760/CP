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
using ld = long double;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;
const ld eps = (ld)1e-20;

int sgn(ld x) {
    return x < -eps ? -1 : x > eps;
}

int cmp(ld x, ld y) {
    return sgn(x - y);
}

struct Point {
    ld x, y;
    Point(){}
    Point(ld x, ld y): x(x), y(y){}
    bool operator <(Point B) const {
        return x == B.x ? y < B.y : x < B.x;
    }
    Point operator -(Point b) const {
        return Point(x - b.x, y - b.y);
    }
    Point operator +(Point b) const {
        return Point(x + b.x, y + b.y);
    }
    Point operator *(ld t) const {
        return Point(x * t, y * t);
    }
    ld operator ^(Point b) {
        return x * b.y - y * b.x;
    }
    ld operator *(Point b) {
        return x * b.x + y * b.y;
    }
    friend int rela(Point a, Point b, Point c) {
        return sgn((b - a) ^ (c - a));
    }
};

struct Line {
    Point p, v;
    ld rad;
    Line(){}
    Line(Point p, Point v):p(p), v(v) {
        rad = atan2l(v.y, v.x);
    }
    Point get_point(ld t) {
        return p + v * t;
    }
    int under(Point a) {
        return rela(p, p + v, a);
    }
    bool operator <(Line b) {
        if (!cmp(rad, b.rad)) {
            return under(b.p) < 0;
        }
        return rad < b.rad;
    }
    Point intersect(Line b) {
        Point u = p - b.p;
        ld t = (b.v ^ u) / (v ^ b.v);
        return get_point(t);
    }
};


vector<Point> half_plane_intersect(vector<Line> lines) {
    sort(all(lines));
    deque<Point> pts;
    deque<Line> ls;
    for (auto l : lines) {
        if (ls.empty()) {
            ls.pb(l);
            continue;
        }
        while (!pts.empty() && l.under(pts.back()) <= 0) {
            pts.pop_back();
            ls.pop_back();
        }
        while (!pts.empty() && l.under(pts[0]) <= 0) {
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
    while (!pts.empty() && ls[0].under(pts.back()) <= 0) {
        pts.pop_back();
        ls.pop_back();
    }
    if (ls.size() > 2) {
        pts.pb(ls[0].intersect(ls.back()));
    }
    return vector<Point>(pts.begin(), pts.end());
}

void solve() {
    assert((sizeof (long double)) == 16);
    int n;
    cin >> n;
    vector up(2, vector<Point>());
    vector down(2, vector<Point>());
    ll rmin = 1e18, lmax = -1e18;
    for (int i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        chkmax(lmax, y1);
        chkmin(rmin, y2);
        down[0].pb({x1, y2});
        up[0].pb({x2, y1});
        down[1].pb({x2, y2});
        up[1].pb({x1, y1});
    }
    if (rmin >= lmax) {
        cout << "possible" << nl;
        return;
    }
    auto cal_up = [&](vector<Point> v) {
        sort(all(v));
        int n = v.size(), top = 0;
        // cerr << "???" << ' ' << n << nl;
        vector<int> st(n + 10);
        for (int i = n - 1; i >= 0; i--) {
            while (top > 1 && sgn((v[st[top]] - v[st[top - 1]]) ^ (v[i] - v[st[top - 1]])) <= 0) {
                top--;
            }
            st[++top] = i;
        }
        vector<Point> res;
        for (int i = 1; i <= top; i++) {
            // cerr << "FF" << ' ' << st[i] << nl;
            res.pb(v[st[i]]);
        }
        return res;
    };
    auto cal_down = [&](vector<Point> v) {
        sort(all(v));
        int n = v.size(), top = 0;
        vector<int> st(n + 10);
        for (int i = 0; i < n; i++) {
            while (top > 1 && sgn((v[st[top]] - v[st[top - 1]]) ^ (v[i] - v[st[top - 1]])) <= 0) {
                top--;
            }
            st[++top] = i;
        }
        vector<Point> res;
        for (int i = 1; i <= top; i++) {
            res.pb(v[st[i]]);
        }
        return res;
    };
    for (int type = 0; type < 2; type++) {
        auto up_convex = cal_up(up[type]);
        auto down_convex = cal_down(down[type]);
        // cerr << "!!up: ";
        // for (auto p : up_convex) cerr << p.x << ' ' << p.y << nl;
        // cerr << "!!down: ";
        // for (auto p : down_convex) cerr << p.x << ' ' << p.y << nl;
        vector<Line> lines;
        lines.pb(Line(up_convex[0], Point(0, 1)));
        for (int i = 0; i + 1 < up_convex.size(); i++) {
            lines.pb(Line(up_convex[i], up_convex[(i + 1) % up_convex.size()] - up_convex[i]));
        }
        lines.pb(Line(up_convex.back(), Point(0, -1)));

        lines.pb(Line(down_convex[0], Point(0, -1)));
        for (int i = 0; i + 1 < down_convex.size(); i++) {
            lines.pb(Line(down_convex[i], down_convex[(i + 1) % down_convex.size()] - down_convex[i]));
        }
        lines.pb(Line(down_convex.back(), Point(0, 1)));

        auto res = half_plane_intersect(lines);
        // cerr << "intersection: " << nl;
        // cerr << res.size() << nl;
        // for (auto p : res) cerr << (double)p.x << ' ' << (double)p.y << nl;
        if (res.size() < 3) {
            cout << "possible" << nl;
            return;
        }
    }
    cout << "impossible" << nl;
    return;
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