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
const int N = 110;
const ll inf = 1e18;
const ll mod = 998244353;
const ld pi = acos(-1);

struct Point{
    ld x, y;
}points[N];

ld dp[N][N][N], dq[N][N][N];

ld operator ^(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

void solve() {
    int n, p;
    cin >> n >> p;
    for (int i = 0; i < n; i++) {
        ld angle;
        cin >> angle;
        ld rad = angle / 180 * pi;
        points[i].x = 1000 * cosl(rad);
        points[i].y = 1000 * sinl(rad);
    }
    memset(dp, -63, sizeof dp);
    for (int i = 0; i < n; i++) {
        auto dq = dp;
        for (int start = 0; start < i; start++) {
            for (int last = 0; last < i; last++) {
                for (int use = 0; use <= i && use < p; use++) {
                    if (dp[start][last][use] >= 0) {
                        chkmax(dq[start][i][use + 1], dp[start][last][use] + (points[last] ^ points[i]));
                    }
                }
            }
        }
        memcpy(dp, dq, sizeof dp);
        dp[i][i][1] = 0;
    }
    ld ans = 0;
    for (int start = 0; start < n; start++) {
        for (int last = start + 1; last < n; last++) {
            chkmax(ans, dp[start][last][p] + (points[last] ^ points[start]));
        }
    }
    cout << fixed << setprecision(10) << ans / 2 << '\n';
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