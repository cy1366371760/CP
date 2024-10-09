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
    ll n, l;
    cin >> n >> l;
    vector<ll> a(n);
    ll mx = -1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    auto calc = [&]() {
        vector<ll> can;
        for (ll i = 1; i <= l - i; i++) {
            ll cur = i * (l - i);
            if (cur <= mx) {
                can.pb(cur);
            }
        }
        vector<ll> dp(mx + 5, inf);
        dp[0] = 0;
        for (ll i = 0; i < mx; i++) {
            for (ll j : can) {
                if (i + j <= mx) {
                    chkmin(dp[i + j], dp[i] + 1);
                }
            }
        }
        return dp;
    };
    auto ans = calc();
    for (int i = 0; i < n; i++) {
        cout << (ans[a[i]] < inf ? ans[a[i]] : -1) << '\n';
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
