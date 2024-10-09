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
    vector<ll> a(n + 5);
    map<ll, vector<int>> hav;
    ll mx = -1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        hav[a[i]].pb(i);
        chkmax(mx, a[i]);
    }
    vector<int> to_l(n + 5), to_r(n + 5);
    vector contain(2, vector<int>(n + 5, 0));
    vector<int> fa(n + 5, 0);
    vector<int> vis(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        to_l[i] = to_r[i] = i;
        fa[i] = i;
        if (a[i] == mx) {
            contain[i & 1][i] = 1;
        }
    }
    function<int(int)> find = [&](int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    };
    int good = 0;
    int cnt = 0;
    ll ans = -1;
    auto chk_good = [&](int i) {
        if (!contain[0][i] && !contain[1][i]) return 0;
        int l = to_l[i], r = to_r[i];
        if ((r - l + 1) % 2 == 0) return 1;
        if ((l & 1) && contain[1][i]) return 1;
        if ((l % 2 == 0) && contain[0][i]) return 1;
        return 0;
    };
    auto del = [&](int i) {
        if (!vis[i]) return;
        int rt = find(i);
        int l = to_l[rt], r = to_r[rt];
        cnt -= (r - l + 2) / 2;
        good -= chk_good(rt);
        return;
    };
    auto merge = [&](int x, int y) {
        x = find(x);
        y = find(y);
        // append x -> y
        assert(x != y);
        for (int tp = 0; tp < 2; tp++) {
            contain[tp][y] |= contain[tp][x];
        }
        chkmin(to_l[y], to_l[x]);
        chkmax(to_r[y], to_r[x]);
        fa[x] = y;
        return y;
    };
    auto ins = [&](int i) {
        vis[i] = 1;
        del(i - 1);
        del(i + 1);
        int rt = i;
        if (vis[i - 1]) rt = merge(rt, i - 1);
        if (vis[i + 1]) rt = merge(rt, i + 1);
        int l = to_l[rt], r = to_r[rt];
        cnt += (r - l + 2) / 2;
        good += chk_good(rt);
    };
    for (auto ii = hav.rbegin(); ii != hav.rend(); ii++) {
        ll mn = (*ii).fi;
        auto &cur = (*ii).sc;
        for (int ps : cur) {
            ins(ps);
        }
        ll nw = mx + mn + cnt;
        if (!good) --nw;
        chkmax(ans, nw);
    }
    cout << ans << nl;
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