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

vector<int> adj[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i <= n + 5; i++) adj[i].clear();
    vector<int> deg(n + 5, 0);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    int rt = -1, leaf = 0;
    vector<bool> is_leaf(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        deg[i] = adj[i].size();
        if (deg[i] > 2) {
            rt = i;
        }
        if (deg[i] == 1) {
            leaf++;
            is_leaf[i] = 1;
        }
    }
    if (rt == -1) {
        for (int i = 1; i <= n + 5; i++) deg[i] = 0, adj[i].clear();
        for (int i = 1; i <= n; i++) {
            if (i & 1) {
                if (i + 2 <= n) {
                    ++deg[i + 2];
                    ++deg[i];
                } else if (i + 1 <= n) {
                    ++deg[i + 1];
                    ++deg[i];
                }
            } else {
                if (i + 1 <= n) {
                    ++deg[i + 1];
                    ++deg[i];
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 1) {
                ans++;
            }
        }
        cout << ans << '\n';
        return;
    }
    vector<vector<int>> dp(n + 5, vector<int>(2, 0));
    function<void(int, int)> dfs = [&](int x, int fa) {
        for (int y : adj[x]) {
            if (y == fa) continue;
            dfs(y, x);
            dp[x][0] += max(dp[y][0], dp[y][1]);
        }
        int tmp = dp[x][0];
        dp[x][1] = dp[x][0];
        for (int y : adj[x]) {
            if (y == fa) continue;
            if (deg[y] == 2) {
                int cur = tmp - max(dp[y][0], dp[y][1]) + dp[y][0] + 1;
                dp[x][1] = max(dp[x][1], cur);
            }
        }
    };
    dfs(1, 0);
    int ans = max(dp[1][0], dp[1][1]) + leaf;
    function<void(int, int, int, int)> dfs2 = [&](int x, int fa, int f0, int f1) {
        int v0 = max(f0, f1) + dp[x][0];
        int v1 = v0;
        {
            if (deg[fa] == 2) {
                int cur = v0 - max(f0, f1) + f0 + 1;
                v1 = max(v1, cur);
            }
        }
        priority_queue<int> pq;
        for (int y : adj[x]) {
            if (y == fa) continue;
            if (deg[y] == 2) {
                int cur = v0 - max(dp[y][0], dp[y][1]) + dp[y][0] + 1;
                pq.push(cur);
                v1 = max(v1, cur);
            }
        }
        for (int y : adj[x]) {
            if (y == fa) continue;
            if (deg[y] == 2) {
                int cur = v0 - max(dp[y][0], dp[y][1]) + dp[y][0] + 1;
                v1 = max(v1, cur);
            }
            int giv0, giv1;
            giv0 = f0 - max(dp[y][0], dp[y][1]);
            if (deg[y] == 2 && v0 - max(dp[y][0], dp[y][1]) + dp[y][0] + 1 == v1) {
                
            }
            dfs2(y, x, , );
        }
    };
    dfs2(1, 0, 0, 0);
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
