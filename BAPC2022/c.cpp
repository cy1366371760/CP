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
    ll t, r;
    ld p;
    cin >> n >> t >> r >> p;
    vector<ld> cost(n + 5);
    cost[0] = 0;
    for (int i = 0; i < n; i++) {
        cost[i + 1] = ((ld)1.0 + p * (cost[i] + r)) / ((ld)1.0 - p);
        cost[i + 1] += cost[i];
    }
    vector<ld> dp(n + 5, 1e18);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            chkmin(dp[i], dp[j] + cost[i - j] + t);
        }
    }
    cout << fixed << setprecision(12) << dp[n] << nl;
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