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
    vector<ll> a(n);
    vector<ll> ans(n + 5, 0);
    ans[1] = n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int fir = 0; fir < n; fir++) {
        for (int sec = fir + 1; sec < n; sec++) {
            ll dt = a[sec] - a[fir];
            vector<ll> dp(n + 5, 0);
            dp[2] = 1;
            for (int i = sec + 1; i < n; i++) {
                vector<ll> dq(n + 5, 0);
                for (int c = 2; c <= n; c++) {
                    dq[c] += dp[c];
                    dq[c] %= mod;
                    if (a[i] - a[fir] == dt * c) {
                        dq[c + 1] += dp[c];
                        dq[c + 1] %= mod;
                    }
                }
                swap(dp, dq);
            }
            for (int i = 1; i <= n; i++) {
                ans[i] += dp[i];
                ans[i] %= mod;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
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
