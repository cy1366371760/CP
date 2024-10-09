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
    int n, m, k;
    cin >> n >> m >> k;
    vector adj(2 * n + 2 * m + 10, vector<pii>());
    for (int i = 1; i <= k; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (y2 < y1) {
            adj[x1].pb({y2 + n, 1});
            adj[y2 + n].pb({x1, 1});
        } else {
            adj[x1].pb({y1 + n, 0});
            adj[y1 + n].pb({x1, 0});
        }
    }
    vector<int> vis(2 * n + 2 * m + 10, -1);
    for (int i = 1; i < vis.size(); i++) {
        if (vis[i] != -1) continue;
        vis[i] = 0;
        vector<int> que;
        que.pb(i);
        for (int q = 0; q < que.size(); q++) {
            int x = que[q];
            for (auto [y, z] : adj[x]) {
                if (~vis[y] && vis[y] == vis[x] ^ z ^ 1) {
                    cout << "No" << nl;
                    return;
                }
                if (vis[y] == -1) {
                    vis[y] = vis[x] ^ z;
                    que.pb(y);
                }
            }
        }
    }
    cout << "Yes" << nl;
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