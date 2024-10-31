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
    int n;
    cin >> n;
    vector<int> ans(n + 5);
    vector<int> val(n + 5);
    vector<int> fr(n + 5);
    vector<int> to(n + 5);
    vector<map<int, int>> idx(n + 5);
    vector adj(n + 5, vector<int>());
    for (int i = 1; i <= n; i++) {
        int x, y, h;
        cin >> x >> y >> h;
        adj[x].pb(y);
        adj[y].pb(x);
        idx[x][y] = idx[y][x] = i;
        fr[i] = x, to[i] = y;
        val[i] = h;
    }
    int tim = 0;
    vector<int> dfn(n + 5, 0);
    vector<int> loop;
    vector<int> stk;
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        stk.pb(x);
        dfn[x] = ++tim;
        bool skp = 0;
        for (int y : adj[x]) {
            if (y == fa && !skp) {
                skp = 1;
                continue;
            }
            if (dfn[y] && dfn[y] < dfn[x]) {
                for (int i = stk.size() - 1; i >= 0; i--) {
                    loop.pb(stk[i]);
                    if (stk[i] == y) break;
                }
                continue;
            }
            if (!dfn[y]) {
                self(self, y, x);
            }
        }
        stk.pop_back();
    };
    dfs(dfs, 1, 0);
    vector<bool> on_loop(n + 5, 0);
    for (int x : loop) on_loop[x] = 1;
    auto label = [&](auto &&self, int x, int fa) -> void {
        for (int y : adj[x]) {
            if (on_loop[y] || y == fa) continue;
            int id = idx[x][y];
            ans[id] = y;
            self(self, y, x);
        }
    };
    auto chk = [&]() -> int {
        vector<set<int>> hav(n + 5);
        bool flg = 1;
        auto upd = [&](int x, int y) -> void {
            if (hav[x].count(y)) flg = 0;
            else {
                hav[x].insert(y);
            }
        };
        for (int i = 1; i <= n; i++) {
            int v = val[i];
            int st = ans[i];
            if (st == fr[i]) {
                upd(fr[i], 1);
                upd(to[i], v);
            } else {
                assert(st == to[i]);
                upd(to[i], 1);
                upd(fr[i], v);
            }
            if (!flg) return 0;
        }
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << ' ';
        }
        cout << nl;
        return 1;
    };
    {
        for (int i = 0; i < loop.size(); i++) {
            int j = (i + 1) % loop.size();
            int x = loop[i], y = loop[j];
            int id = idx[x][y];
            ans[id] = x;
        }
        for (int x : loop) {
            label(label, x, 0);
        }
        if(chk()) return;
    }
    {
        for (int i = 0; i < loop.size(); i++) {
            int j = (i + 1) % loop.size();
            int x = loop[i], y = loop[j];
            int id = idx[x][y];
            ans[id] = y;
        }
        for (int x : loop) {
            label(label, x, 0);
        }
        if(chk()) return;
    }
    cout << "impossible" << nl;
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