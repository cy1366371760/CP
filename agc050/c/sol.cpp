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

ll dp[N][22], row_sum[N][22];

void solve() {
    string s;
    cin >> s;
    int n = s.length();
    ll tot = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '?') {
            tot = tot * 2 % mod;
        }
    }
    int bound = n;
    dp[n][0] = 1;
    row_sum[n][0] = 1;
    vector<ll> mn_dis(22, 0);
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '?') {
            for (int j = 1; j <= 21; j++) {
                int d;
                if (j == 1) d = 0;
                else d = 1 << (j - 2);
                int fr = i + d + 1;
                if (fr > bound) continue;
                dp[i][j] = (row_sum[fr][j - 1] -
                row_sum[bound + 1][j - 1] + mod) % mod;
            }
        } else if (s[i] == 'B') {
            for (int j = 1; j <= 21; j++) {
                int d;
                if (j == 1) d = 0;
                else d = 1 << (j - 2);
                int fr = i + d + 1;
                if (fr > bound) continue;
                dp[i][j] = (row_sum[fr][j - 1] -
                row_sum[bound + 1][j - 1] + mod) % mod;
            }
            bound = i;
        }
        for (int j = 0; j <= 21; j++) {
            row_sum[i][j] = (dp[i][j] + row_sum[i + 1][j]) % mod;
        }
    }
    ll lose = 0;
    for (int i = bound; i >= 0; i--) {
        for (int j = 0; j <= 21; j++) {
            lose = (lose + dp[i][j]) % mod;
        }
    }
    cout << (tot - lose + mod) % mod;
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