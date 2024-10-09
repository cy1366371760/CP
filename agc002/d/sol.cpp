#include<bits/stdc++.h>

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
    vector<pii> edges(m + 5);
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].fi >> edges[i].sc;
    }
    vector<int> fa(n + 5, 0), sz(n + 5, 1);
    iota(all(fa), 0);
    vector<array<int, 4>> qrys;
    int qq;
    cin >> qq;
    for (int i = 1; i <= qq; i++) {
        array<int, 4> qry;
        cin >> qry[0] >> qry[1] >> qry[2];
        qry[3] = i;
        qrys.pb(qry);
    }
    vector<int> ans(qq + 1, 0);
    vector<array<int, 3>> history;
    
    auto find = [&](auto &&self, int x) -> int {
        return fa[x] == x ? x : self(self, fa[x]);
    };

    auto append = [&](pii nw) {
        auto [x, y] = nw;
        int fx = find(find, x);
        int fy = find(find, y);
        if (fx == fy) return;
        if (sz[fx] > sz[fy]) swap(x, y), swap(fx, fy);
        history.pb({0, fy, sz[fy]});
        history.pb({1, fx, fx});

        sz[fy] += sz[fx];
        fa[fx] = fy;
    };

    auto chk = [&](auto &&self, int tl, int tr, vector<array<int, 4>> qrys) -> void {
        if (tl == tr) {
            for (auto [x, y, z, id] : qrys) {
                ans[id] = tl;
            }
            return;
        }
        int mid = (tl + tr) >> 1;
        int top = history.size();
        for (int i = tl; i <= mid; i++) {
            append(edges[i]);
        }
        vector<array<int, 4>> qrys_l, qrys_r;
        // cerr << "!!!" << mid << ' ' << sz[find(find, 1)] << '\n';
        for (auto qry : qrys) {
            auto [x, y, z, id] = qry;
            int cur = sz[find(find, x)];
            if (find(find, x) != find(find, y)) {
                cur += sz[find(find, y)];
            }
            if (cur >= z) qrys_l.pb(qry);
            else qrys_r.pb(qry);
        }
        self(self, mid + 1, tr, qrys_r);
        while (history.size() > top) {
            auto [type, x, y] = history.back();
            history.pop_back();
            if (type == 0) {
                sz[x] = y;
            } else {
                fa[x] = y;
            }
        }
        self(self, tl, mid, qrys_l);
    };
    chk(chk, 1, m, qrys);
    for (int i = 1; i <= qq; i++) {
        cout << ans[i] << '\n';
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