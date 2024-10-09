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
    int n; ll T;
    cin >> n >> T;
    vector<ll> later;
    vector<pll> prev;
    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        if (a == 0) {
            later.pb(b + 1);
        } else {
            prev.pb({a, b});
        }
    }
    sort(all(later));
    sort(all(prev), [](pll u, pll v) {
        return u.fi * (v.sc + 1) > (u.sc + 1) * v.fi;
    });
    vector<ll> dp(31, (ll)1e9 + 5);
    dp[0] = 0;
    for (auto [a, b] : prev) {
        auto dq = dp;
        for (int i = 0; i < 30; i++) {
            chkmin(dq[i + 1], dp[i] + 1 + a * (dp[i] + 1) + b);
        }
        swap(dp, dq);
    }
    for (int i = 0; i + 1 < later.size(); i++) {
        later[i + 1] += later[i];
    }
    ll ans = 0;
    for (ll pre = 0; pre <= 30; pre++) {
        if (dp[pre] > T) continue;
        ll las = T - dp[pre];
        chkmax(ans, pre + (upper_bound(all(later), las) - later.begin()));
    }
    cout << ans << '\n';
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