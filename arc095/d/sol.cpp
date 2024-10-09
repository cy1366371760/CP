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
    vector adj(n + 1, vector<int>());
    vector imp_adj(n + 1, vector<int>());
    vector son_leaf(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    if (n == 2) {
        cout << 1 << ' ' << 2 << nl;
        return;
    }
    vector<int> is_leaf(n + 1, 0);
    vector<int> imp;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() == 1) {
            is_leaf[i] = 1;
        } else {
            imp.pb(i);
            // cerr << "GG" << i << nl;
            for (int j : adj[i]) {
                if (adj[j].size() == 1) {
                    son_leaf[i].pb(j);
                    // cerr << "son_leaf: " << j << nl;
                } else {
                    imp_adj[i].pb(j);
                    // cerr << "imp_adj: " << j << nl;
                }
            }
        }
    }
    vector<int> may_bg;
    for (int x : imp) {
        int deg = imp_adj[x].size();
        if (deg >= 3) {
            cout << -1 << nl;
            return;
        }
        if (deg <= 1) {
            may_bg.pb(x);
        }
    }
    if (may_bg.size() > 2) {
        cout << -1 << nl;
        return;
    }
    vector<int> ans;
    vector<int> cur;
    auto dfs = [&](auto &&self, int x, int fa, int idx) -> void {
        // cerr << "dfs:" << x << ' ' << fa << ' ' << idx << nl;
        int nw = ++idx;
        for (int i = 1; i <= son_leaf[x].size(); i++) {
            ++idx;
            cur.pb(idx);
        }
        cur.pb(nw);
        for (int y : imp_adj[x]) {
            if (y == fa) continue;
            self(self, y, x, idx);
        }
    };
    vector<int> real_bg;
    if (may_bg.size() == 1) {
        may_bg.pb(may_bg.back());
    }
    for (auto bg : may_bg) {
        int leaf = son_leaf[bg].back();
        son_leaf[bg].pop_back();
        imp.pb(leaf);
        imp_adj[leaf].pb(bg);
        imp_adj[bg].pb(leaf);
        real_bg.pb(leaf);
    }
    for (int bg : real_bg) {
        cur.clear();
        // cerr << "???" << bg << nl;
        dfs(dfs, bg, 0, 0);
        if (cur.size() == n) {
            if (ans.empty()) ans = cur;
            else ans = min(ans, cur);
        }
    }
    if (ans.empty()) cout << -1 << nl;
    else {
        for (int x : ans) cout << x << ' ';
        cout << nl;
    }
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