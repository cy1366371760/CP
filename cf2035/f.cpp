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

pll pq[N];
int ptop;

void solve() {
    int n, rt;
    cin >> n >> rt;
    vector adj(n + 5, vector<int>());
    vector<ll> a(n + 5, 0), val(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    int tim = 0;
    vector<int> dfn(n + 5, 0);
    vector<pii> seg(n + 5);
    auto dfs = [&](auto &&self, int x, int fa) -> void {
        dfn[x] = ++tim;
        val[dfn[x]] = a[x];
        for (int y : adj[x]) {
            if (y == fa) continue;
            self(self, y, x);
        }
        seg[x] = pii(dfn[x], tim);
    };
    dfs(dfs, rt, 0);
    // for (int i = 1; i <= n; i++) {
    //     cerr << seg[i].fi << ' ' << seg[i].sc << nl;
    // }
    // for(int i = 1; i <= n; i++) {
    //     cerr << dfn[i] << ' ';
    // }
    // cerr << nl;
    ll res = 1e18;
    vector<pll> laz(n + 5);
    auto chk = [&](ll tim, ll ex) -> bool {
        for (int i = 1; i <= n; i++) {
            ll cnt = tim;
            if (i <= ex) {
                ++cnt;
            }
            int l = seg[i].fi;
            int r = seg[i].sc;
            // cerr << "shit" << cnt << ' ' << l << ' ' << r << nl;
            laz[l] = pll(r, cnt);
        }
        ptop = 0;
        for (int i = 1; i <= n; i++) {
            {
                auto [r, cnt] = laz[i];
                if (cnt) pq[++ptop] = pll(r, cnt);
            }
            ll want = val[i];
            while (want) {
                if (ptop == 0) return 0;
                auto [r, cc] = pq[ptop--];
                ll del = min(want, cc);
                want -= del;
                cc -= del;
                if (cc) pq[++ptop] = pll(r, cc);
            }
            ll sum = 0;
            while (ptop && pq[ptop].fi == i) {
                sum += pq[ptop--].sc;
            }
            if (sum & 1) {
                if (!ptop) return 0;
                auto [r, cc] = pq[ptop--];
                --cc;
                if (cc) {
                    pq[++ptop] = pll(r, cc);
                }
            }
        }
        return 1;
    };
    // chk(1, 1);
    // exit(0);
    ll l = 0, r = 1e9;
    vector valid(n + 5, vector<bool>(2, 1));
    while (l <= r) {
        ll mid = (l + r) >> 1;
        bool ifok = 0;
        vector<pii> nvalid;
        for (int ex = 0; ex < n; ex++) {
            if (valid[ex][0] && chk(mid * 2, ex)) {
                chkmin(res, mid * 2 * n + ex);
                ifok = 1;
            } else nvalid.pb({ex, 0});
            if (valid[ex][1] && chk(mid * 2 + 1, ex)) {
                chkmin(res, (mid * 2 + 1) * n + ex);
                ifok = 1;
            } else nvalid.pb({ex, 1});
        }
        if (!ifok) l = mid + 1;
        else {
            r = mid - 1;
            for (auto [ex, t] : nvalid) {
                valid[ex][t] = 0;
            }
        }
    }
    if (res == (ll)1e18) res = -1;
    cout << res << nl;
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