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
const int mod = 167772161;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> w(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    auto Add = [&](int &x, int y) -> void {
        x = (x + y) % mod;
    };
    auto Sub = [&](int &x, int y) -> void {
        x = (x - y + mod) % mod;
    };
    vector ans(n + 2, vector<int>(n + 2, 0));
    vector dp(vector(n + 2, vector<int>(k + 2, 0)));
    dp[0][0] = 1;
    for (int i = 1; i <= n + n - 1; i++) {
        // cerr << "!!" << i << nl;
        int nw = (i <= n ? w[i] : w[i - n]);
        int idx = (i <= n ? i : i - n);
        if (i >= n) {
            for (int j = 1; j < n; j++) {
                for (int v = k - nw + 1; v <= k; v++) {
                    Add(ans[idx][j], dp[j][v]);
                }
            }
        }
        if (i >= n) {
            int del = w[i - n + 1];
            vector g(vector(n + 2, vector<int>(k + 2, 0)));
            g[1][del] = 1; // contains del
            for (int j = 1; j < n; j++) {
                for (int v = 0; v <= k; v++) {
                    Sub(dp[j][v], g[j][v]);
                    if (v + del <= k) {
                        Add(g[j + 1][v + del], dp[j][v]);
                    }
                }
            }
        }
        auto dq = dp;
        for (int j = 0; j < min(i, n); j++) {
            for (int v = 0; v + nw <= k; v++) {
                Add(dq[j + 1][v + nw], dp[j][v]);
            }
        }
        swap(dp, dq);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < n; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << nl;
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