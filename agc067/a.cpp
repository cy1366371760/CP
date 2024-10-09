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

bool linked[5050][5050];

int fr[N], to[N];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        fr[i] = x, to[i] = y;
    }
    if (m < 1LL * (n / 2) * (n / 2 - 1) / 2) {
        cout << "No" << '\n';
        return;
    }
    for (int i = 1; i <= m; i++) {
        int x = fr[i], y = to[i];
        linked[x][y] = linked[y][x] = 1;
    }
    // cerr << "??" << '\n';
    vector<bool> vis(n + 5, 0);
    vector<int> fa(n + 5, 0), dep(n + 5, 0);
    bool flg = 0;
    auto dfs = [&](auto &&self, int x, int ff) -> void {
        // cerr << "!!" << x << ' ' << ff << '\n';
        vis[x] = 1;
        fa[x] = ff;
        for (int y = 1; y <= n; y++) {
            if (y == x || y == ff) continue;
            if (linked[x][y]) continue;
            if (vis[y]) {
                if ((dep[x] & 1) == (dep[y] & 1)) {
                    flg = 1;
                    // cerr << x << ' ' << y << '\n';
                }
            } else {
                dep[y] = dep[x] + 1;
                self(self, y, x);
            }
        }
    };
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dep[i] = 1, dfs(dfs, i, 0);
    }
    cout << (flg ? "No" : "Yes") << '\n';
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            linked[i][j] = 0;
        }
    }
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