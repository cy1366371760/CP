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
const ld pi = acos(-1);
#define pld pair<ld, ld>
const ld eps = 1e-10;

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}
    Point rotate(ld rad) {  // 逆时针旋转 rad 弧度    
        return Point(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad));  
    }
}a[N];

mt19937 rng(time(0));

void solve() {
    int n;
    cin >> n;
    // n = 200000;
    for (int i = 1; i <= n; i++) {
        int xx, yy;
        cin >> xx >> yy;
        // xx = rng();
        // yy = rng();
        a[i].x = xx, a[i].y = yy;
        a[i] = a[i].rotate(pi / 4);
    }
    // cerr << "!!" << ' ' << n << '\n';
    auto check = [&](ld p) {
        vector<pld> cur;
        // cerr << "???" << p << '\n';
        for (int i = 1; i <= n; i++) {
            Point v = a[i];
            // cerr << "fafa" << ' ' << v.y - p * v.x << ' ' << v.y + p * v.x << '\n';
            cur.eb(v.y - p * v.x, v.y + p * v.x);
        }
        sort(all(cur));
        ld mx = -inf;
        for (auto &v : cur) {
            if (v.sc <= mx) return 1;
            chkmax(mx, v.sc);
        }
        return 0;
    };
    ld ans = 1;
    for (int swp = 0; swp <= 1; swp++) {
        sort(a + 1, a + n + 1, [&](Point x, Point y) {
            return x.x < y.x;
        });
        for (int i = 1; i < n; i++) {
            if (a[i].x == a[i + 1].x) continue;
            ld cur = (a[i + 1].y - a[i].y) / (a[i + 1].x - a[i].x);
            cur = fabs(cur);
            cur = min(cur, (ld)1.0 / cur);
            chkmin(ans, cur);
        }
        for (int i = 1; i <= n; i++) {
            swap(a[i].x, a[i].y);
        }
    }
    ld y;
    if (fabs(ans - 1) < eps) {
        cout << fixed << setprecision(12) << 1.0 << '\n';
        return;
    }
    y = (1 + ans) / (1 - ans);
    cout << fixed << setprecision(12) << (1 + y) / sqrtl(1 + y * y) << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}
