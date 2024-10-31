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
const ld eps = 1e-20;

int sgn(ld x) {
    return x < 0 ? -1 : x > 0;
}

struct Point {
    ld x, y;
    Point() {}
    Point(ld x, ld y) : x(x), y(y){}
    ld operator ^(Point b) {
        return x * b.y - y * b.x;
    }
    Point operator -(Point b) {
        return Point(x - b.x, y - b.y);
    }
    bool operator <(Point b) {
        return x == b.x ? y < b.y : x < b.x;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<Point> a;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        a.pb(Point(x - 1, y));
        a.pb(Point(x + 1, y));
        a.pb(Point(x, y - 1));
        a.pb(Point(x, y + 1));
    }
    sort(all(a));
    if (n == 1) {
        cout << 4 << nl;
        return;
    }
    n = 4 * n;
    vector<int> st(n + 10);
    int top = 0;
    for (int i = 0; i < n; i++) {
        if (top > 1 && sgn((a[st[top]] - a[st[top - 1]]) ^ (a[i] - a[st[top - 1]])) <= 0) {
            --top;
        }
        st[++top] = i;
    }
    int k = top;
    for (int i = n - 2; i >= 0; i--) {
        if (top > k && sgn((a[st[top]] - a[st[top - 1]]) ^ (a[i] - a[st[top - 1]])) <= 0) {
            --top;
        }
        st[++top] = i;
    }
    for (int i = 1; i <= top; i++) {
        cerr << a[st[i]].x << ' ' << a[st[i]].y << nl;
    }
    ll res = 0;
    if (top - 1 == 2) {
        res += 2;
        int u = st[1], v = st[2];
        if (abs(a[u].x - a[v].x) == abs(a[u].y - a[v].y)) {
            res++;
        }
    } else if (top - 1 != 4) {
        res = 4 - (top - 1);
    }
    for (int i = 1; i < top; i++) {
        int u = st[i], v = st[i + 1];
        res += max(abs(a[u].x - a[v].x), abs(a[u].y - a[v].y));
    }
    cout << res << nl;
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