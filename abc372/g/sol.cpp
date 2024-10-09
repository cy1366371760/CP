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

struct Line {
    ll a, b, c;
    ld x0, y0;
    Line () {

    };
    Line (ll a, ll b, ll c): a(a), b(b), c(c) {
        y0 = (ld)1.0 * c / b;
        x0 = (ld)1.0 * c / a;
    };
}line[N];

ll floor_sum(ll a, ll b, ll c, ll n) { // sum i=0...n, floor((a*i + b)/c)
    if (a == 0) {  
        return (n + 1) * (b / c) ;  
    }  
    ll mx = (a * n + b) / c; // 0, mx - 1  
    if (mx == 0) {  
        return 0;  
    }  
    if (a >= c || b >= c) {  
        return (n * (n + 1) / 2 * (a / c)  + (n + 1) * (b / c) + floor_sum(a % c, b % c, c, n));  
    }  
    return (mx * (n + 1) - floor_sum(c, a + c - b - 1, a, mx - 1));
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        --c;
        line[i] = Line(a, b, c);
    }
    auto cmp_x0 = [&](Line u, Line v) {
        ll tmp_x = v.a * u.c - v.c * u.a;
        return tmp_x < 0 ? -1 : tmp_x > 0;
    };
    auto cmp_y0 = [&](Line u, Line v) {
        ll tmp_y = v.b * u.c - v.c * u.b;
        return tmp_y < 0 ? -1 : tmp_y > 0;
    };
    sort(line + 1, line + n + 1, [&](auto u, auto v) {
        auto sgn_x = cmp_x0(u, v);
        auto sgn_y = cmp_y0(u, v);
        return (sgn_y == 0 ? sgn_x < 0 : sgn_y < 0);
    });
    // for (int i = 1; i <= n; i++) {
    //     cerr << line[i].y0 << nl;
    // }
    Line mn = line[1];
    vector<Line> maybe;
    maybe.pb(line[1]);
    for (int i = 2; i <= n; i++) {
        auto sgn_x = cmp_x0(mn, line[i]);
        if (sgn_x <= 0) {
            continue;
        }
        mn = line[i];
        maybe.pb(line[i]);
    }
    vector<Line> stk;
    for (auto u : maybe) {
        ll a2, b2, c2;
        a2 = u.a, b2 = u.b, c2 = u.c;
        while (stk.size() >= 2) {
            ll a0, b0, c0, a1, b1, c1;
            auto p = stk.end()[-2], q = stk.end()[-1];
            a0 = p.a, b0 = p.b, c0 = p.c;
            a1 = q.a, b1 = q.b, c1 = q.c;
            __int128 fuck = (__int128)(c1 * b0 - c0 * b1) * (a2 * b0 - a0 * b2);
            fuck -= (__int128)(c2 * b0 - c0 * b2) * (a1 * b0 - a0 * b1);
            int sgn = 1;
            if (a1 * b0 - a0 * b1 < 0) sgn ^= 1;
            if (a2 * b0 - a0 * b2 < 0) sgn ^= 1;
            if ((sgn == 1 && fuck >= 0) || (sgn == 0 && fuck <= 0)) {
                stk.pop_back();
            } else break;
        }
        stk.pb(u);
    }
    // cerr << "shittt" << nl;
    ll las = 1;
    // auto under = [&](Line p, ll x, ll y) {
    //     return p.a * x + p.b * y <= p.c;
    // };
    // auto calc_y(Line p, ll x) {
    //     return 
    // };
    auto under = [&](ll x, Line p, Line q) {
        return (ld)1.0 * (p.c - x * p.a) / p.b <= (ld)1.0 * (q.c - x * q.a) / q.b;
    };
    auto upper = [&](ll x, Line p, Line q) {
        return (ld)1.0 * (p.c - x * p.a) / p.b > (ld)1.0 * (q.c - x * q.a) / q.b;
    };
    auto calc = [&](Line p, Line q) {
        ld a0, b0, c0, a1, b1, c1;
        a0 = p.a, b0 = p.b, c0 = p.c;
        a1 = q.a, b1 = q.b, c1 = q.c;
        ld x_meet = (ld)1.0 * (c1 - (ld)1.0 * c0 * b1 / b0) / (a1 - (ld)1.0 * a0 * b1 / b0);
        // cerr << x_meet << nl;
        ll x = (ll)x_meet;
        while (upper(x + 1, q, p)) ++x;
        while (under(x, q, p)) --x;
        return x;
    };
    auto doit = [&](ll a, ll b, ll c, ll n) {
        ll res = 0;
        ll p = c / b;
        if (c % b) ++p;
        ll d = -c + p * b;
        d = (b - 1 + d);
        // cerr << "fuck" << a << ' ' << d << ' ' << ' ' << b << ' ' << n << nl;
        res = -p * (n + 1) + floor_sum(a, d, b, n);
        return -res;
    };
    ll ans = 0;
    for (int i = 0; i < (int)stk.size(); i++) {
        ll lb = las, rb;
        ll a, b, c;
        a = stk[i].a;
        b = stk[i].b;
        c = stk[i].c;
        if (i + 1 < (int)stk.size()) {
            rb = calc(stk[i], stk[i + 1]);
        } else {
            rb = (ll)stk[i].x0;
            while ((rb + 1) * a <= c) ++rb;
            while (rb * a > c) --rb;
        }
        // cerr << "miao?" << i << ' ' << a << ' ' << b << ' ' <<c << ' ' << lb << ' ' << rb << nl;
        if (lb <= rb) {
            ans += doit(a, b, c, rb);
            ans -= doit(a, b, c, lb - 1);
            // cerr << "shit" << doit(a, b, c, rb) << ' ' << doit(a, b, c, lb - 1) << nl;
        }
        // cerr << "GG" << ans << nl;
        assert(rb + 1 >= lb);
        // las = max(las, rb + 1);
        las = rb + 1;
    }
    cout << ans << nl;
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