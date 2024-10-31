#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define nl '\n'
using namespace std;
const int N = 1010;
using BST = bitset<N>;

struct SAT {
    int n, tim, num;
    bool valid;
    vector<vector<int>> adj;
    vector<int> dfn, low, stk, bel;
    vector<bool> ins, hav;

    SAT() {}
    SAT(int n) { // i = sel, i + n = non-sel
        this -> n = n;
        tim = num = 0;
        valid = 1;
        stk.clear();
        adj.assign(2 * n + 5, {});
        dfn.assign(2 * n + 5, 0);
        low.assign(2 * n + 5, 0);
        bel.assign(2 * n + 5, 0);
        ins.assign(2 * n + 5, 0);
        hav.assign(2 * n + 5, 0);
    }
void init(int n) { // i = sel, i + n = non-sel
        this -> n = n;
        for (int i = 0; i <= n * 2; i++) {
            adj[i].clear();
            dfn[i] = low[i] = 0;
            ins[i] = 0;
            hav[i] = bel[i] = 0;
        }
        stk.clear();
        tim = 0;
        num = 0;
        valid = 1;
    }
    void dfs(int x) {
        dfn[x] = low[x] = ++tim;
        ins[x] = 1;
        stk.pb(x);
        for (auto v : adj[x]) {
            if (!dfn[v]) {
                dfs(v);
                if (!valid) return;
                low[x] = min(low[x], low[v]);
            } else if (ins[v]) {
                low[x] = min(low[x], dfn[v]);
            }
        }
        if (low[x] == dfn[x]) {
            ++num;
            vector<int> bin;
            while (1) {
                int nw = stk.back();
                stk.pop_back();
                if (nw > n && hav[nw - n] || nw <= n && hav[nw + n]) {
                    valid = false;
                    return;
                }
                hav[nw] = 1, ins[nw] = 0, bel[nw] = num;
                bin.pb(nw);
                if (nw == x) break;
            }
            for (auto v : bin) hav[v] = 0;
            bin.clear();
        }
    }
    void add_edge(int x, int y) {
        adj[x].pb(y);
    }
    pair<bool, vector<int>> sol() {
        valid = 1;
        for (int i = 1; i <= n * 2; i++) {
            if (!dfn[i]) dfs(i);
        }
        vector<int> sel(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            sel[i] = (bel[i] < bel[i + n]);
        }
        return make_pair(valid, sel);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<BST> linked(n + 5);
    vector adj(n + 5, vector<int>());
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        linked[x][y] = linked[y][x] = 1;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    for (int i = 1; i <= n; i++) {
        linked[i][i] = 1;
    }
    vector<int> manager;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() <= 15) {
            BST nw;
            for (int j : adj[i]) {
                nw |= linked[j];
            }
            if (nw.count() == n) {
                if (adj[i].size() > 10 && manager.empty()) {
                    int sz = adj[i].size();
                    for (int s = 0; s < (1 << sz); s++) {
                        if (__builtin_popcount(s) == 10) {
                            BST tmp;
                            for (int j = 0; j < sz; j++) {
                                if (s >> j & 1) {
                                    tmp |= linked[adj[i][j]];
                                }
                            }
                            if (tmp.count() == n) {
                                for (int j = 0; j < sz; j++) {
                                    if (s >> j & 1) {
                                        manager.pb(adj[i][j]);
                                    }
                                }
                                break;
                            }
                        }
                    }
                } else {
                    if (manager.empty() || adj[i].size() < manager.size()) {
                        manager = adj[i];
                    }
                }
            }
        }
    }
    assert(!manager.empty());
    BST tmp;
    vector<int> top(n + 5, -1);
    vector<bool> is_m(n + 5, 0);
    for (int i = 0; i < manager.size(); i++) {
        top[manager[i]] = i;
        is_m[manager[i]] = 1;
    }
    for (int i = 0; i < manager.size(); i++) {
        int m = manager[i];
        for (int x : adj[m]) {
            if (top[x] == -1) {
                top[x] = i;
            }
        }
    }
    // for (int m : manager) cerr << m << ' ' ;
    int B = manager.size();
    vector<int> wh(n + 5, 0);
    SAT sat(n);
    for (int s = 0; s < (1 << B); s++) {
        // cerr << "GG" << ' ' << s << nl;
        if (~s & 1) continue;
        sat.init(n);
        for (int m : manager) {
            sat.add_edge(m, m + n);
        }
        for (int i = 1; i <= n; i++) {
            if (is_m[i]) wh[i] = (s >> top[i] & 1);
            else wh[i] = 1 - (s >> top[i] & 1);
        }
        for (int x = 1; x <= n; x++) {
            // if (s == 1) cerr << "shit" << x << ' ' << top[x] << nl;
            for (int y : adj[x]) {
                if (x > y) continue;
                if (wh[x] == wh[y]) {
                    sat.add_edge(x, y + n);
                    sat.add_edge(y, x + n);
                    sat.add_edge(x + n, y);
                    sat.add_edge(y + n, x);
                } else {
                    sat.add_edge(x, y + n);
                    sat.add_edge(y, x + n);
                }
            }
        }
        auto [valid, sel] = sat.sol();
        if (valid) {
            // cerr << bitset<3>(s) << nl;
            for (int i = 1; i <= n; i++) {
                if (sel[i]) cout << 3 << ' ';
                else {
                    cout << wh[i] + 1 << ' ';
                }
            }
            cout << nl;
            exit(0);
        }
    }
    cout << "Impossible" << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}