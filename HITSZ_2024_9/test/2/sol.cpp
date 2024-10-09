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
    int n; ll m;
    cin >> n >> m;
    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
    }
    ll B = sqrtl(m);
    while (B * B <= m) ++B;
    vector dp1(B + 5, vector<ll>(m + 5, -1));
    vector dp2(B + 5, vector<ll>(m + 5, -1));
    dp2[0][0] = 0;
    // cerr << B << ' ' << nl;
    for (int i = 1; i <= n; i++) {

        vector dq1(B + 5, vector<ll>(m + 5, -1));
        vector dq2(B + 5, vector<ll>(m + 5, -1));
        // dp2 -> dq2 & dq1
        {
            for (int pre = B; pre >= 0; pre--) {
                for (int wt = 0; wt <= m; wt++) {
                    chkmax(dq2[pre][wt], dp2[pre][wt]);
                    if (dp2[pre][wt] >= 0) {
                        chkmax(dp1[B + 1][wt], dp2[pre][wt]);
                        chkmax(dq1[B + 1][wt], dp2[pre][wt]);
                    }
                    if (wt + pre <= m) {
                        if (dp2[pre][wt] >= 0) {
                            chkmax(dp2[pre][wt + pre], dp2[pre][wt]);
                        }
                    }
                    if (pre + w[i] <= B && wt + pre + w[i] * (B + 1) <= m && dp2[pre][wt] >= 0) {
                        chkmax(dq2[pre + w[i]][wt + pre + w[i] * (B + 1)], dp2[pre][wt] + v[i]);
                    }
                }
            }
        }

        // dp1 -> dq1
        {
            for (int sel = B; sel >= 1; sel--) {
                for (int wt = 0; wt <= m; wt++) {
                    chkmax(dq1[sel][wt], dp1[sel][wt]);
                    if (dp1[sel + 1][wt] >= 0) chkmax(dp1[sel][wt], dp1[sel + 1][wt]);
                    if (wt + w[i] * sel <= m && dp1[sel + 1][wt] >= 0) {
                        chkmax(dq1[sel][wt + w[i] * sel], dp1[sel + 1][wt] + v[i]);
                    }
                }
            }
        }

        swap(dp1, dq1);
        swap(dp2, dq2);
    }
    pll ans = {-1, -1};
    for (int i = 0; i <= B; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp1[i][j] >= 0) {
                chkmax(ans, pll(j, dp1[i][j]));   
            }
            if (dp2[i][j] >= 0) {
                if (j + i <= m) {
                    chkmax(dp2[i][i + j], dp2[i][j]);
                }
                chkmax(ans, pll(j, dp2[i][j]));
            }
        }
    }
    cout << ans.fi << ' ' << ans.sc << nl;
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