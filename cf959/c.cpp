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
    int n; ll x;
    cin >> n >> x;
    vector<ll> a(n + 5, 0);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    for (int i = n + 1; i < a.size(); i++) {
        a[i] = inf;
    }
    ll ans = 0;
    vector<ll> dp(n + 5, 0);
    for (int l = n; l >= 1; l--) {
        int ps = upper_bound(a.begin() + l, a.end(), a[l - 1] + x) - a.begin();
        dp[l] = (ps - l) + dp[ps + 1];
        ans += dp[l];
    }
    cout << ans << '\n';
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
