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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> imp(n + 1, 0);
    int rt = -1;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        imp[x] = 1;
        rt = x;
    }
    vector adj(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    vector<int> sz(n + 1, 0);
    vector<int> rem(n + 1, 0);
    int ans = 0;
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        for (int y : adj[x]) {
            if (y == fa) continue;
            self(self, y, x);
            imp[x] |= rem[y];
        }
        if (imp[x]) {
            int odd = 0;
            for (int y : adj[x]) {
                if (y == fa) continue;
                int nw = sz[y];
                if (nw & 1) {
                    if (odd) {
                        odd = 0;
                        --nw;
                        ans += nw / 2;
                    } else {
                        ans += (nw + 1) / 2;
                        odd = 1;
                    }
                } else {
                    ans += nw / 2;
                }
            }
            if (odd) {
                rem[x] = 1;
            }
            sz[x] = 0;
        } else {
            sz[x] = 1;
            for (int y : adj[x]) {
                if (y == fa) continue;
                sz[x] += sz[y];
            }
        }
    };
    dfs(dfs, rt, 0);
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