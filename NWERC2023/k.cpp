#include<bits/stdc++.h>
#define ll long long
#define int long long
#define pii pair<int, int>
#define fi first
#define sc second
#define pb push_back
#define all(x) x.begin(),x.end()
#define nl '\n'
using namespace std;

bool vis[510][510][2];

vector<pii> get_dir(int x, int y) {
    vector<pii> res;
    for (int t = 0; t < 2; t++) {
        for (int i = -1; i <= 1; i += 2)
            for (int j = -1; j <= 1; j += 2)
                res.pb({i * x, j * y});
        swap(x, y);
    }
    return res;
}

void solve() {
    int n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;
    vector<tuple<int, int, int>> que;
    vis[1][1][0] = 1;
    vis[1][1][1] = 1;
    que.pb({1, 1, 0});
    que.pb({1, 1, 1});
    for (int q = 0; q < que.size(); q++) {
        auto [x, y, t] = que[q];
        auto dirs = (t == 0 ? get_dir(a, b) : get_dir(c, d));
        for (auto [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;
            int nt = t ^ 1;
            if(nx >= 1 && nx <= n && ny >= 1 && ny <= n && !vis[nx][ny][nt]) {
                vis[nx][ny][nt] = 1;
                que.pb({nx, ny, nt});
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            res += (vis[i][j][0] || vis[i][j][1]);
        }
    }
    cout << res << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}