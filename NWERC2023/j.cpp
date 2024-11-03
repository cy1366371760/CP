#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define fi first
#define sc second
#define pb push_back
#define all(x) x.begin(),x.end()
#define nl '\n'
using namespace std;
const ll inf = 1e18;
using ld = long double;
const ld eps = 1e-20;
const ld pi = acosl(-1);
template <class T>
void chkmin(T &a, T b) {
    if (a > b) a = b;
}

int sgn(ld x) {
    return x < -eps ? -1 : x > eps;
}

struct Point {
    ld x, y;
    Point(){}
    Point(ld x, ld y): x(x), y(y){}
    Point rotate(ld ang) {
        return Point(x * cosl(ang) - y * sinl(ang), x * sinl(ang) + y * cosl(ang));
    }
    Point operator -(Point b) const {
        return Point(x - b.x, y - b.y);
    }
    ld rad() {
        return atan2l(y, x);
    }
};

ld dis(Point a, Point b) {
    return fabsl(a.x - b.x) + fabsl(a.y - b.y);
}

void solve() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    int lim = (1 << n) - 1;
    auto chk = [&](ld ang) {
        vector<Point> b(n);
        for (int i = 0; i < n; i++) {
            b[i] = a[i].rotate(ang);
        }
        vector dp(lim + 5, vector<ld>(n + 5, 1e18));
        for (int i = 0; i < n; i++) {
            dp[1 << i][i] = 0;
        }
        for (int sta = 0; sta <= lim; sta++) {
            for (int j = 0; j < n; j++) {
                if (sta >> j & 1) {
                    for (int i = 0; i < n; i++) {
                        if (sta >> i & 1) continue;
                        chkmin(dp[sta | (1 << i)][i], dp[sta][j] + dis(b[i], b[j]));
                    }
                }
            }
        }
        ld res = 1e18;
        for (int las = 0; las < n; las++) {
            chkmin(res, dp[lim][las]);
        }
        return res;
    };
    ld ans = chk(0);
    ld l = 0, r = pi / 2.0, m1, m2;
    for (int i = 1; i <= 100; i++) {
        ld len = (r - l) / 3.0;
        m1 = l + len;
        m2 = m1 + len;
        ld fir = chk(m1), sec = chk(m2);
        if (sgn(fir - sec) <= 0) r = m2;
        else l = m1;
        ans = min(ans, fir);
        ans = min(ans, sec);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Point vec = a[j] - a[i];
            ld ang = vec.rad();
            ans = min(ans, chk(ang));
            ans = min(ans, chk(-ang));
            ans = min(ans, chk(pi / 2 + ang));
            ans = min(ans, chk(pi / 2 - ang));
        }
    }
    cout << fixed << setprecision(10) << ans << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}