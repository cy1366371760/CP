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
const int inf = 1e9;
const ll mod = 998244353;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pii> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].fi >> a[i].sc;
        if (a[i].fi > a[i].sc) {
            swap(a[i].fi, a[i].sc);
        }
    }
    sort(all(a));
    a.erase(unique(all(a)), a.end());
    m *= 2;
    vector adj(m + 1, vector<int>());
    for (auto [x, y] : a) {
        if (x == y)  {
            int nx = x + m / 2;
            adj[x].pb(nx);
            adj[nx].pb(x);
        } else {
            adj[x].pb(y);
            adj[y].pb(x);
        }
    }
    int tim = 0;
    vector<int> dfn(m + 1, 0);
    vector<int> stk;
    vector<int> loop;
    vector<int> cur;
    vector<int> dep(m + 1, 0);
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        dfn[x] = ++tim;
        stk.pb(x);
        cur.pb(x);
        for (int y : adj[x]) {
            if (y == fa) continue;
            if (dfn[y] && dfn[y] < dfn[x]) {
                if (loop.size()) {
                    cout << "impossible" << nl;
                    exit(0);
                }
                for (int i = stk.size() - 1; i >= 0; i--) {
                    loop.pb(stk[i]);
                    if (stk[i] == y) break;
                }
            } else if (!dfn[y]) {
                dep[y] = dep[x] + 1;
                self(self, y, x);
            }
        }
        stk.pop_back();
    };
    vector<int> fafa(m + 1, 0);
    auto dfs2 = [&](auto &&self, int x, int fa) -> void {
        fafa[x] = fa;
        for (int y : adj[x]) {
            if (y == fa) continue;
            dep[y] = dep[x] + 1;
            self(self, y, x);
        }
    };
    for (int i = 1; i <= m; i++) {
        if (!dfn[i]) {
            cur.clear();
            dfs(dfs, i, 0);
        }
    }
    if (loop.size()) {
        vector<int> dis(m + 1, (int)1e9);
        vector<int> que;
        for (int x : loop) dis[x] = 0, que.pb(x);
        for (int q = 0; q < que.size(); q++) {
            int x = que[q];
            for (int y : adj[x]) {
                if (dis[y] >= inf) {
                    dis[y] = dis[x] + 1;
                    que.pb(y);
                }
            }
        }
        int res = -1;
        for (int i = 1; i <= m; i++) {
            if (adj[i].size()) {
                chkmax(res, dis[i]);
            }
        }
        if (res > 1) {
            cout << "impossible" << nl;
        } else cout << "possible" << nl;
        return;
    }
    fill(all(dfn), 0);
    fill(all(dep), 0);
    tim = 0;
    vector<int> st;
    for (int i = 1; i <= m; i++) {
        if (!dfn[i]) {
            cur.clear();
            dfs(dfs, i, 0);
            int who = i;
            for (int x : cur) {
                if (dep[x] > dep[who]) {
                    who = x;
                }
            }
            dep[who] = 0;
            dfs2(dfs2, who, 0);
            int who2 = who;
            for (int x : cur) {
                if (dep[x] > dep[who2]) {
                    who2 = x;
                }
            }
            while (1) {
                st.pb(who2);
                if (who2 == who) break;
                who2 = fafa[who2];
            }
        }
    }
    vector<int> dis(m + 1, inf);
    vector<int> que;
    for (int x : st) dis[x] = 0, que.pb(x);
    for (int q = 0; q < que.size(); q++) {
        int x = que[q];
        for (int y : adj[x]) {
            if (dis[y] >= inf) {
                dis[y] = dis[x] + 1;
                que.pb(y);
            }
        }
    }
    int res = -1;
    for (int i = 1; i <= m; i++) {
        if (adj[i].size()) {
            chkmax(res, dis[i]);
        }
    }
    if (res > 1) {
        cout << "impossible" << nl;
    } else cout << "possible" << nl;
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