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
    vector<int> lb(n + 1), rb(n + 1);
    vector<int> buk;
    for (int i = 1; i <= n; i++) {
        cin >> lb[i] >> rb[i];
        rb[i] += lb[i];
        buk.pb(lb[i]);
        buk.pb(rb[i]);
    }
    sort(all(buk));
    buk.erase(unique(all(buk)), buk.end());
    int lim = buk.size() + 5;
    vector hav(lim, vector<pii>());
    for (int i = 1; i <= n; i++) {
        int l = lower_bound(all(buk), lb[i]) - buk.begin();
        int r = lower_bound(all(buk), rb[i]) - buk.begin();
        hav[l].pb(pii(r, i));
    }
    vector<int> dp;
    vector<int> ans(n + 1);
    dp.pb((int)1e9);
    for (int t = 0; t < lim; t++) {
        sort(all(hav[t]), [&](pii a, pii b) {
            return a.fi > b.fi;
        });
        for (auto [x, id] : hav[t]) {
            int ps = upper_bound(all(dp), x, greater<int>()) - dp.begin() - 1;
            ans[id] = ps;
            if (ps == dp.size() - 1) {
                dp.pb(x);
            } else {
                dp[ps + 1] = x;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
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