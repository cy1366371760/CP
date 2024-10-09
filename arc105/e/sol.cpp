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

struct DSU {
    vector<int> fa;
    vector<int> sz;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        fa.resize(n + 5);
        iota(all(fa), 0);
        sz.resize(n + 5);
        fill(all(sz), 1);
        sz[0] = 0;
    }
    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int merge(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy) return 0;
        if (sz[fx] > sz[fy]) {
            swap(x, y);
            swap(fx, fy);
        }
        fa[fx] = fy;
        sz[fy] += sz[fx];
        return 1;
    }
    int size(int x) {
        return sz[find(x)];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        dsu.merge(x, y);
    }
    set<int> ban;
    int fir = dsu.size(1) & 1, sec = dsu.size(n) & 1;
    ban.insert(dsu.find(1));
    ban.insert(dsu.find(n));
    // cerr << 1 << ' ' << dsu.size(1) << nl;
    // cerr << n << ' ' << dsu.size(n) << nl;
    int odd = 0;
    int las = 0;
    auto calc = [&](int x) {
        x = dsu.size(x);
        return (1LL * x * (x - 1) / 2LL) % 2;
    };
    las += calc(1);
    las += calc(n);
    for (int i = 2; i < n; i++) {
        int nw = dsu.find(i);
        if (nw == i && !ban.count(nw)) {
            // cerr << nw << ' ' << dsu.size(nw) << nl;
            if (dsu.size(i) & 1) {
                ++odd;
            }
            las += calc(nw);
        }
    }
    las = las & 1;
    if (m & 1) las ^= 1;
    vector dp(2, vector(2, vector(2, vector<int>(n + 1, -1))));
    // cerr << "!!" << fir << ' ' << sec << ' ' << las << ' ' << odd << nl;
    auto dfs = [&](auto &&self, int fir, int sec, int las, int num) -> bool {
        // cerr << fir << ' ' << sec << ' ' << las << ' ' << num << nl;
        if (dp[fir][sec][las][num] != -1) return dp[fir][sec][las][num];
        if (las == 0 && num == 0) return dp[fir][sec][las][num] = 0;
        int res = 0;
        if (las == 1) {
            res |= 1 - self(self, fir, sec, las ^ 1, num);
        }
        if (num >= 2) {
            res |= 1 - self(self, fir, sec, las, num - 2);
        }
        if (num) {
            if (fir == 0) {
                res |= 1 - self(self, fir ^ 1, sec, las ^ 1, num - 1);
            } else {
                res |= 1 - self(self, fir ^ 1, sec, las, num - 1);
            }
            if (sec == 0) {
                res |= 1 - self(self, fir, sec ^ 1, las ^ 1, num - 1);
            } else {
                res |= 1 - self(self, fir, sec ^ 1, las, num - 1);
            }
        }
        // cerr << "GGG" << fir << ' ' << sec << ' ' << las << ' ' << num << ' ' << res << nl;
        return dp[fir][sec][las][num] = res;
    };
    cout << (dfs(dfs, fir, sec, las, odd) ? "First" : "Second") << endl;
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