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
    int n;
    cin >> n;
    vector<int> a(n + 5);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector diff(n + 5, vector<int>(2, 0));
    diff[0][0] = 0;
    diff[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == a[i - 1]) {
            diff[i] = diff[i - 1];
        } else {
            diff[i][0] = i - 1;
            if (a[diff[i - 1][0]] != a[i]) diff[i][1] = diff[i - 1][0];
            else diff[i][1] = diff[i - 1][1];
        }
    }
    vector<ll> dp(n + 5, 0);
    vector<ll> sum_dp(n + 5, 0);
    int bound = 1;
    dp[1] = sum_dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] == a[i - 1]) {
            dp[i] = dp[i - 1];
            bound = i;
        } else {
            ll res = 0;
            if (bound == i - 1) {
                res = dp[i - 1];
            } else { // 3 1 2 
                // if (i == n - 1) {
                //     cerr << "fuck" << bound << ' ' << diff[i][1] << '\n';
                // } 4 3 5 3 5
                res = (dp[i - 1] + dp[i - 2]) % mod;
                int bf = min(i - 3, diff[i][1]);
                if (bound <= bf) {
                    res = (res + sum_dp[bf] - sum_dp[bound - 1] + mod + mod) % mod;
                }
            }
            dp[i] = res;
        }
        sum_dp[i] = (sum_dp[i - 1] + dp[i]) % mod;
        // cerr << i << ' ' << a[i] << ' ' << dp[i] << '\n';
    }
    cout << dp[n] << '\n';
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