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
#define int long long

void solve() {
    int n, m;
    cin >> n >> m;
    ll mx = 0;
    vector<pii> a(n + 5);
    for (int i = 1; i <= n; i++) {
        int len;
        cin >> len;
        vector<bool> vis(len + 5, 0);
        for (int j = 1; j <= len; j++) {
            int x;
            cin >> x;
            if (x <= len + 4) {
                vis[x] = 1;
            }
        }
        ll A, B;
        bool skip = 0;
        for (int j = 0; j <= len + 3; j++) {
            if (!vis[j]) {
                if (skip) {
                    B = j;
                    break;
                }
                A = j;
                skip = 1;
            }
        }
        chkmax(mx, B);
        a[i] = pii(A, B);
    }
    vector<ll> dp(mx + 5, 0);
    vector adj(mx + 5, vector<int>());
    for (int i = 1; i <= n; i++) {
        auto [A, B] = a[i];
        adj[A].pb(B);
    }

    iota(all(dp), 0LL);
    ll bas = 0;
    for (int i = mx + 4; i >= 0; i--) {
        for (int j : adj[i]) {
            chkmax(dp[i], dp[j]);
        }
        if (adj[i].size() > 1) {
            chkmax(bas, dp[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        auto [A, B] = a[i];
        chkmax(bas, A);
    }
    int lim = min(m, mx + 4);
    ll res = 0;
    for (int i = 0; i <= lim; i++) {
        ll cur = max({i, dp[i], bas});
        res += cur;
    }
    if (lim < m) {
        ++lim;
        res += (m + lim) * (m - lim + 1) / 2LL;
    }
    cout << res << '\n';
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