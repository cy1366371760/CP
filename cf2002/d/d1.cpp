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

mt19937_64 rng(time(0));

void solve() {
    int n, qq;
    cin >> n >> qq;
    vector<int> fa(n + 5, 0);
    vector<vector<int>> adj(n + 5);
    vector<int> sz(n + 5, 0);
    vector<ll> rnd_val(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        rnd_val[i] = i;
    }
    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
        adj[fa[i]].pb(i);
    }
    vector<ll> need(n + 5, 0), cur(n + 5, 0);
    auto dfs = [&](auto &&self, int x) -> void {
        sz[x] = 1;
        map<ll, int> ocr;
        ll nw = 1;
        for (auto y : adj[x]) {
            self(self, y);
            sz[x] += sz[y];
            ocr[nw] += 1;
            nw = sz[y];
        }
        // cerr << "FHDFUIHD" << x << '\n';
        for (auto [val, c] : ocr) {
            need[x] += rnd_val[val] * c;
            // cerr << val << ' ' << c << '\n';
        }
        // cerr << "fdf" << need[x] << '\n';
    };
    dfs(dfs, 1);

    vector<int> p(n + 5, 0), wh(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        wh[p[i]] = i;
    }
    vector<set<int>> hav(n + 5);
    vector<map<int, ll>> ocr(n + 5);
    int ok_num = 0;
    vector<int> ifok(n + 5, 0);
    auto hsh_ins = [&](int x, ll val) {
        cur[x] -= rnd_val[val] * ocr[x][val];
        ++ocr[x][val];
        cur[x] += rnd_val[val] * ocr[x][val];
        return;
    };
    auto hsh_del = [&](int x, ll val) {
        cur[x] -= rnd_val[val] * ocr[x][val];
        --ocr[x][val];
        cur[x] += rnd_val[val] * ocr[x][val];
        return;
    };
    auto append = [&](int x, int y) {
        if (x == 0) return;
        // cerr << "append" << x << ' ' << y << '\n';
        if (ifok[x]) {
            ifok[x] = 0;
            ok_num--;
        }
        auto ii = hav[x].lower_bound(y);
        if (ii == hav[x].begin()) {
            if (ii != hav[x].end()) {
                hsh_ins(x, (*ii) - y);
            }
            hav[x].insert(y);
        } else {
            auto jj = prev(ii);
            ll small = (*jj);
            if (ii == hav[x].end()) {
                hsh_ins(x, y - small);
            } else {
                ll big = (*ii);
                hsh_del(x, big - small);
                hsh_ins(x, big - y);
                hsh_ins(x, y - small);
            }
            hav[x].insert(y);
        }
        if (wh[x] == (*hav[x].begin()) && cur[x] == need[x]) {
            ifok[x] = 1;
            ++ok_num;
        }
    };
    auto erase = [&](int x, int y) {
        if (x == 0) return;
        // cerr << "erase" << ' ' << x << ' ' << y << '\n';
        if (ifok[x]) {
            ifok[x] = 0;
            ok_num--;
        }
        auto ii = hav[x].lower_bound(y);
        if (ii == hav[x].begin()) {
            if (ii != hav[x].end()) {
                auto jj = next(ii);
                if (jj != hav[x].end()) {
                    hsh_del(x, (*jj) - y);
                }
            }
            hav[x].erase(y);
        } else {
            auto jj = prev(ii);
            auto kk = next(ii);
            ll small = (*jj);
            if (kk == hav[x].end()) {
                hsh_del(x, y - small);
            } else {
                ll big = (*kk);
                hsh_del(x, y - small);
                hsh_del(x, big - y);
                hsh_ins(x, big - small);
            }
            hav[x].erase(y);
        }
        if (wh[x] == (*hav[x].begin()) && cur[x] == need[x]) {
            ifok[x] = 1;
            ++ok_num;
        }
    };
    for (int ps = 1; ps <= n; ps++) {
        int x = p[ps];
        append(x, ps);
        append(fa[x], ps);
    }
    while (qq--) {
        int ps1, ps2;
        cin >> ps1 >> ps2;
        int x = p[ps1], y = p[ps2];
        wh[y] = ps1;
        wh[x] = ps2;
        p[ps1] = y;
        p[ps2] = x;
        erase(fa[x], ps1);
        erase(fa[y], ps2);
        erase(x, ps1);
        erase(y, ps2);
        append(fa[x], ps2);
        append(fa[y], ps1);
        append(x, wh[x]);
        append(y, wh[y]);
        if (ok_num == n) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }
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