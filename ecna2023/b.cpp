#include<bits/stdc++.h>
#define pb push_back
#define nl '\n'
using namespace std;

using ld = long double;

void solve() {
    int m, n, k;
    ld s;
    cin >> m >> n >> k >> s;
    s /= 2.0;
    n += m;
    vector<ld> a(n + 5);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.begin() + n + 1);
    vector<ld> sum(n + 5, 0), sum2(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
        sum2[i] = sum2[i - 1] + a[i] * a[i];
    }
    vector cost(n + 5, vector<ld>(n + 5, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ld nw = s * s * (j - i + 1);
            ld ss = (sum[j] - sum[i - 1]);
            ld x = ss / (j - i + 1);
            nw += x * x * (j - i + 1);
            nw += sum2[j] - sum2[i - 1];
            nw -= 2 * ss * x;
            cost[i][j] = nw;
        }
    }
    vector dp(n + 5, vector<ld>(k + 5, 1e18));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= k; c++) {
            for (int j = 0; j < i; j++) {
                dp[i][c] = min(dp[i][c], dp[j][c - 1] + cost[j + 1][i]);
            }
        }
    }
    cout << fixed << setprecision(10);
    cout << dp[n][k] << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}