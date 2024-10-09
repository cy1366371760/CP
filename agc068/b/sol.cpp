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
    vector<int> bel(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> bel[i];
    }
    vector<int> nxt(n + 1);
    {
        vector<int> las(n + 1, -1);
        for (int i = n; i >= 1; i--) {
            int nw = bel[i];
            if (las[nw] == -1) nxt[i] = i;
            else nxt[i] = las[nw];
            las[nw] = i;
        }
    }
    auto chk = [&](vector<int> fir, vector<int> sec) {
        int dt0 = count(all(fir), 0) - count(all(sec), 0);
        int dt1 = count(all(fir), 1) - count(all(sec), 1);
        if (dt0 || dt1) {
            cout << "GG cnt" << nl;
            return;
        }
        vector<int> fa(fir.size() + 5, 0);
        iota(all(fa), 0);
        auto find = [&](auto &&self, int x) -> int {
            return fa[x] == x ? x : fa[x] = self(self, fa[x]);
        };
        auto mg = [&](int x, int y) {
            x = find(find, x);
            y = find(find, y);
            if (x == y) return;
            if (x < y) swap(x, y);
            fa[x] = y;
        };
        for (int type = 0; type < 2; type++) {
            int ptr = 0;
            for (int i = 0; i < fir.size(); i++) {
                if (fir[i] == type) {
                    while (sec[ptr] != type) ++ptr;
                    mg(i + 1, ptr + 1);
                    ++ptr;
                }
            }
        }
        vector<int> res(n + 1);
        int cnt = 0;
        map<int, int> vis;
        for (int i = 1; i <= n; i++) {
            int nw = find(find, i);
            if (!vis.count(nw)) vis[nw] = ++cnt;
            res[i] = vis[nw];
        }
        assert(res == bel);
    };
    vector<int> up, down;
    vector<int> las_down;
    for (int i = 1; i <= n; i++) {
        up.pb(0);
        down.pb(1);
    }
    las_down = down;
    for (int i = 1; i <= n; i++) {
        up.insert(up.end(), all(las_down));
        las_down.clear();
        for (int j = 1; j <= n; j++) {
            las_down.pb(1);
        }
        int to = nxt[i];
        las_down[to - 1] = 0;
        down.insert(down.end(), all(las_down));
    }
    for (int i = 1; i <= n; i++) {
        up.insert(up.end(), all(las_down));
        las_down.clear();
        for (int j = 1; j <= n; j++) {
            las_down.pb(1);
        }
        las_down[i - 1] = 0;
        down.insert(down.end(), all(las_down));
    }
    up.insert(up.end(), all(las_down));
    las_down.clear();
    for (int j = 1; j <= n; j++) {
        las_down.pb(0);
    }
    down.insert(down.end(), all(las_down));

    // chk(up, down);
    cout << up.size() << nl;
    for (int x : up) cout << x;
    cout << nl;
    for (int x : down) cout << x;
    cout << nl;
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