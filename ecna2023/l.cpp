#include<bits/stdc++.h>
#define pb push_back
#define nl '\n'
#define pii pair<int, int>
#define fi first
#define sc second
#define all(u) (u).begin(),(u).end()
using namespace std;

using ld = long double;

const int order[][3] = {{3, 0, 1}, {0, 1, 2}, {1, 2, 3}, {2, 3, 0}}; 

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pii> coord(n + 5);
    vector nxt(n + 5, vector<pii>(4, pii(-1, 0)));
    for (int i = 1; i <= n; i++) {
        cin >> coord[i].fi >> coord[i].sc;
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        auto pu = coord[u];
        auto pv = coord[v];
        if (pu.sc == pv.sc && pu.fi < pv.fi) {
            nxt[u][1] = pii(v, w);
            nxt[v][3] = pii(u, w);
        } else if (pu.sc == pv.sc && pu.fi > pv.fi) {
            nxt[u][3] = pii(v, w);
            nxt[v][1] = pii(u, w);
        } else if (pu.fi == pv.fi && pu.sc < pv.sc) {
            nxt[u][0] = pii(v, w);
            nxt[v][2] = pii(u, w);
        } else {
            assert(pu.fi == pv.fi && pu.sc > pv.sc);
            nxt[u][2] = pii(v, w);
            nxt[v][0] = pii(u, w);
        }
    }
    int nw;
    string tmp;
    int dir;
    cin >> nw >> tmp;
    if (tmp == "N") dir = 0;
    else if (tmp == "E") dir = 1;
    else if (tmp == "S") dir = 2;
    else dir = 3;
    auto rev = [&](int x) {
        if (x == 0) return 2;
        if (x == 1) return 3;
        if (x == 2) return 0;
        return 1;
    };
    while (1) {
        // cerr << nw << ' ' << dir << ' ' << nxt[nw][dir].fi << ' ' << nxt[nw][dir].sc << nl;
        vector<pii> edges;
        vector vis(n + 5, vector<bool>(4, 0));
        bool ocr_0 = 0;
        auto go_nxt = [&](int &nw, int &dir) -> void {
            int to = nxt[nw][dir].fi;
            int nxt_dir = -1;
            // cerr << (char)('A' + nw - 1) << ' ' << (char)('A' + to - 1) << nl;
            nxt[nw][dir].sc -= 1;
            nxt[to][rev(dir)].sc -= 1;
            if (nxt[nw][dir].sc == 0) {
                ocr_0 = 1;
            }
            edges.pb({nw, dir});
            vector<int> ok;
            for (auto d : order[dir]) {
                if (nxt[to][d].sc > 0) {
                    ok.pb(d);
                }
            }
            if (ok.size() == 0) {
                nxt_dir = -1;
            } else if (ok.size() == 1) {
                nxt_dir = ok[0];
            } else if (ok.size() == 2) {
                nxt_dir = ok[0];
            } else {
                nxt_dir = ok[1];
            }
            nw = to;
            dir = nxt_dir;
        };
        while (!vis[nw][dir] && !ocr_0) {
            vis[nw][dir] = 1;
            go_nxt(nw, dir);
            if (dir == -1) {
                cout << coord[nw].fi << ' ' << coord[nw].sc << nl;
                return;
            }
        }
        if (ocr_0) continue;
        vector<pii> loop;
        while (!(edges.back().fi == nw && edges.back().sc == dir)) {
            loop.pb(edges.back());
            edges.pop_back();
        }
        loop.pb(edges.back());
        // for (int i = loop.size() - 1; i >= 0; i--) {
        //     cerr << loop[i].fi << ' ' << loop[i].sc << ' ' << nxt[loop[i].fi][loop[i].sc].fi << ' ' << nxt[loop[i].fi][loop[i].sc].sc << nl;
        // }
        int mn = 1e9;
        vector is_loop(n + 5, vector<bool>(4, 0));
        for (auto [fr, d] : loop) {
            is_loop[fr][d] = 1;
        }
        for (auto [fr, d] : loop) {
            if (is_loop[nxt[fr][d].fi][rev(d)]) {
                mn = min(mn, (nxt[fr][d].sc - 1) / 2);
            } else {
                mn = min(mn, nxt[fr][d].sc - 1);
            }
        }
        for (auto [fr, d] : loop) {
            nxt[fr][d].sc -= mn;
            nxt[nxt[fr][d].fi][rev(d)].sc -= mn;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}