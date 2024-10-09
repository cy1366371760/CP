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
    int n = 5;
    vector<int> side{4, 6, 8, 12, 20};
    vector<int> cnt(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> cnt[i];
    }
    vector<ld> dp(1010, 0.0);
    int mx = 0, mn = 0;
    dp[0] = 1.0;
    for (int i = 0; i < n; i++) {
        int nw = side[i];
        for (int c = 0; c < cnt[i]; c++) {
            vector<ld> dq(1010, 0.0);
            ld p = 1.0 / nw;
            for (int j = mn; j <= mx; j++) {
                for (int v = 1; v <= nw; v++) {
                    dq[j + v] += dp[j] * p;
                }
            }
            mn += 1;
            mx += nw;
            swap(dp, dq);
        }
    }
    vector<pair<ld, int>> res;
    for (int i = mn; i <= mx; i++) {
        res.pb({dp[i], i});
    }
    sort(all(res));
    reverse(all(res));
    for (auto [_, i] : res) cout << i << ' ';
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