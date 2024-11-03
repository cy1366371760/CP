#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define fi first
#define sc second
#define pb push_back
#define all(x) x.begin(),x.end()
#define nl '\n'
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    auto ask = [&](int x, int y) -> int {
        cout << x << ' ' << y << endl;
        string res;
        cin >> res;
        if (res == "miss") return 0;
        if (res == "hit") return 1;
        if (res == "sunk") --k;
        if (k == 0) exit(0);
        return 2;
    };
    vector vis(n + 5, vector<bool> (n + 5, 0));
    vector<pii> dirs;
    dirs.pb({1, 1});
    dirs.pb({5, 0});
    dirs.pb({0, 5});
    vector<pii> may;
    auto dfs = [&](auto &&self, int x, int y) -> void {
        vis[x][y] = 1;
        int re = ask(x, y);
        if (re == 1) {
            may.pb({x, y});
        }
        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && !vis[nx][ny]) {
                self(self, nx, ny);
            }
        }
    };
    dfs(dfs, 1, 1);
    assert(may.size() == k);
    for (auto [x, y] : may) {
        for (int i = max(x - 4, 1); i <= min(n, x + 4); i++) {
            ask(i, y);
        }
        for (int j = max(y - 4, 1); j <= min(n, y + 4); j++) {
            ask(x, j);
        }
    }
}

signed main() {
    solve();
}