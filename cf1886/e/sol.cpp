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
#define int long long

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n), b(m);
    map<int, vector<int>> idx;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        idx[a[i]].pb(i + 1);
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(all(a));
    vector<int> dp(1 << m, n + 5);
    vector<int> las(1 << m, -1);
    vector<pii> seg(1 << m);
    dp[0] = 0;
    int all = (1 << m) - 1;
    /*

        i >= bg
        min{i + ceil(b[nxt] / a[i])}
        -> min(j)
        exist i >= bg
        (j - i + 1) * a[i] >= b[nxt]
        j * a[i] - (i - 1) * a[i] >= b[nxt]
        j >= (b[nxt] + (i - 1) * a[i]) / a[i]
        j >= (i - 1) + b[nxt] / a[i]
    */
    vector mn_go(m, vector<int>(n, n + 5));
    vector mn_st(m, vector<int>(n, n + 5));
    for (int bit = 0; bit < m; bit++) {
        int nw = b[bit];
        for (int i = n - 1; i >= 0; i--) {
            int step = a[i];
            int need = (nw / step);
            if (nw % step) ++need;
            int mn_ps = i + need - 1;
            if (mn_ps < n) {
                mn_go[bit][i] = mn_ps;
                mn_st[bit][i] = i;
            }
            if (i < n - 1) {
                if (chkmin(mn_go[bit][i], mn_go[bit][i + 1])) {
                    mn_st[bit][i] = mn_st[bit][i + 1];
                }
            }
        }
    }
    for (int sta = 0; sta <= all; sta++) {
        if (dp[sta] >= n) continue;
        int bg = dp[sta];
        for (int nxt = 0; nxt < m; nxt++) {
            if (sta >> nxt & 1) continue;
            int to = sta | (1 << nxt);
            int mn_ps = mn_go[nxt][bg];
            if (mn_ps >= n) continue;
            if (chkmin(dp[to], mn_ps + 1)) {
                las[to] = nxt;
                seg[to] = pii(mn_st[nxt][bg], mn_ps);
            }
        }
    }
    if (dp[all] > n) {
        cout << "NO" << nl;
    } else {
        cout << "YES" << nl;
        int nw = all;
        vector<pii> ans(m + 10);
        while (nw) {
            int lst = las[nw];
            ans[lst] = seg[nw];
            nw ^= 1 << lst;
        }
        for (int i = 0; i < m; i++) {
            auto [l, r] = ans[i];
            cout << r - l + 1 << ' ';
            for (int x = l; x <= r; x++) {
                int val = a[x];
                cout << idx[val].back() << ' ';
                idx[val].pop_back();
            }
            cout << nl;
        }
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