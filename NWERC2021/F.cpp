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
using ld = __float128;
const int N = 1e6 + 100;
const ll inf = 1e18;
const ll mod = 998244353;
const ld eps = 1e-30;

int sgn(ld x) {
    return x < -eps ? -1 : x > eps;
}

struct Point {
    ld x, y;
    Point(){}
    Point(ld x, ld y) : x(x), y(y){}
    bool operator == (Point b) {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    bool operator < (Point b) {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : sgn(x - b.x) < 0;
    }
    bool operator <= (Point b) {
        return ((*this) == b || (*this) < b);
    }
    Point operator -(Point b) {
        return Point(x - b.x, y - b.y);
    }
    Point operator +(Point b) {
        return Point(x + b.x, y + b.y);
    }
    ld operator ^(Point b) {
        return x * b.y - y * b.x;
    }
    ld operator *(Point b) {
        return x * b.x + y * b.y;
    }
    ld length() {
        return hypotl(x, y);
    }
};

ld get_angle(Point a, Point b) {
    // cerr << "fuck" << ' ' << (double)a * b << ' ' << a.length() << ' ' << b.length() << nl;
    return -((a * b) / a.length() / b.length());
}

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
    {
        ll x, y;
        cin >> x >> y;
        s = Point(x, y);
        cin >> x >> y;
        t = Point(x, y);
    }
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }
    vector<Point> up, down;
    ll pos = 0, neg = 0;
    for (auto p : a) {
        ld ang1, ang2;
        ang1 = get_angle(p - s, t - s);
        ang2 = get_angle(p - t, s - t);
        if (sgn((p - s) ^ (t - s)) == 0) {
            if (sgn((t - s) * (p - s)) > 0) ++pos;
            else ++neg;
        } else if (sgn((p - s) ^ (t - s)) > 0) {
            down.pb({ang1, ang2});
        } else {
            up.pb({ang1, ang2});
        }
    }
    auto calc = [&](vector<Point> cur) {
        sort(all(cur));
        memset(fen, 0, sizeof fen);
        vector<Point> buk;
        for (auto p : cur) {
            buk.pb({p.y, 0});
        }
        sort(all(buk));
        buk.erase(unique(all(buk)), buk.end());
        ll res = 0;
        for (auto p : cur) {
            int ps = lower_bound(all(buk), Point(p.y, 0)) - buk.begin() + 1;
            // cerr << "!!" << fixed << setprecision(30) << p.x << ' ' << p.y << nl;
            // cerr << ps << nl;
            res += ask(ps);
            add(ps);
        }
        return res;
    };
    cout << calc(up) + calc(down) + (pos * (pos - 1) + neg * (neg - 1)) / 2LL << nl;
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