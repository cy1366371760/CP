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
const ll mod = 1e9 + 7;

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}

void solve() {
    int n, m;
    cin >> n >> m;
    int lim = 1;
    while (1LL * (lim + 1) * (lim + 2) / 2LL <= m) ++lim;
    vector dp(lim + 1, vector<ll>(m + 1, 0));
    vector sum(lim + 1, vector<ll>(m + 1, 0));
    dp[0][0] = 1;
    for (int val = 0; val <= m; val++) {
        sum[0][val] = dp[0][val];
        if (val >= n) {
            Add(sum[0][val], sum[0][val - n]);
        }
    }
    for (int i = 1; i <= lim; i++) {
        int per = i * (i + 1) / 2;
        dp[i] = dp[i - 1];
        for (int val = per; val <= m; val++) {
            Add(dp[i][val], dp[i][val - per]);
        }
        for (int val = 0; val <= m; val++) {
            sum[i][val] = dp[i][val];
            if (val >= n) {
                Add(sum[i][val], sum[i][val - n]);
            }
        }
    }
    ll ans = 0;
    for (int ps = 1; ps <= n; ps++) {
        int las = m - (ps - 1) * (ps) / 2;
        if (las < 0) {
            break;
        }
        int left = ps - 1, right = n - ps;
        chkmin(left, lim);
        chkmin(right, lim);
        for (int l = 0; l <= las; l++) {
            Add(ans, 1LL * dp[left][l] * sum[right][las - l]);
        }
    }
    cout << ans << nl;
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