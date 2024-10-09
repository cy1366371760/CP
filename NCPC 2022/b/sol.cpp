#include<bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(),(x).end()
using namespace std;
const ll inf = 1e18;

void solve() {
    int n;
    cin >> n;
    vector adj(n + 5, vector<int>());
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    vector<int> dep(n + 5, 0);
    vector<int> ff(n + 5, 0);
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        ff[x] = fa;
        for (int y : adj[x]) {
            if (y == fa) continue;
            dep[y] = dep[x] + 1;
            self(self, y, x);
        }
    };
    dep[1] = 0;
    dfs(dfs, 1, 0);
    vector<int> ed(2, 0);
    ed[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (dep[i] > dep[ed[0]]) {
            ed[0] = i;
        }
    }
    fill(all(ff), 0);
    fill(all(dep), 0);
    dfs(dfs, ed[0], 0);
    ed[1] = ed[0];
    for (int i = 1; i <= n; i++) {
        if (dep[i] > dep[ed[1]]) {
            ed[1] = i;
        }
    }
    if (dep[ed[1]] <= 2) {
        cout << "NO" << nl;
        return;
    }
    cout << "YES" << nl;
    vector<int> imp(n + 5, 0);
    int tmp = ed[1];
    do {
        imp[tmp] = 1;
        tmp = ff[tmp];
    } while (tmp != 0);
    auto dfs2 = [&](auto &&self, int x, int fa) -> void {
        int nxt = -1;
        for (int y : adj[x]) {
            if (y == fa) continue;
            if (imp[y]) {
                nxt = y;
                continue;
            }
            cout << y << ' ';
            self(self, y, x);
        }
        if (nxt != -1) {
            cout << nxt << ' ';
            self(self, nxt, x);
        }
    };
    int bg = ff[ed[1]];
    dfs2(dfs2, bg, ed[1]);
    cout << bg << ' ' << ed[1] << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}