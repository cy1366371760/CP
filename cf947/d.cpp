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

int n, a, b;
vector<int> adj[N];
int fa[N], dep[N];
void solve() {
    cin >> n >> a >> b;
    for (int i = 0; i <= n; i++) {
        adj[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    function<void(int, int)> dfs = [&](int x, int ff) {
        for (int y : adj[x]) {
            if (y == ff) continue;
            fa[y] = x;
            dep[y] = dep[x] + 1, dfs(y, x);
        }
    };
    dep[a] = 0, dfs(a, 0);
    int ans = 0;
    ans += (dep[b] + 1) / 2;
    int step = (dep[b] + 1) / 2;
    int rt = b;
    for (int i = 0; i < step; i++) {
        rt = fa[rt];
    }
    // cerr << ans << ' ' << rt << '\n';
    int mx = 0;
    function<void(int, int)> dfs2 = [&](int x, int ff) {
        int son = 0;
        int son_mx = 0;
        for (int y : adj[x]) {
            if (y == ff) continue;
            dep[y] = dep[x] + 1, dfs2(y, x);
        }
        chkmax(mx, dep[x]);
    };
    dep[rt] = 0, dfs2(rt, 0);
    ans += 2 * (n - 1);
    ans -= mx;
    cout << ans << '\n';
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
