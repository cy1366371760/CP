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
const int N = 310;
const ll inf = 1e18;
const ll mod = 1e9 + 7;

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector dp(n + 5, vector<ll>(n + 5, 0));
    dp[1][1] = 1;
    for (int i = 1; i <= m; i++) {
        vector dq(n + 5, vector<ll>(n + 5, 0));
        for (int num = 1; num <= i && num <= n; num++) {
            for (int sz = 1; sz <= num; sz++) {
                ll cur = dp[num][sz];
                if (cur == 0) continue;
                if (num < n) {
                    Add(dq[num + 1][sz], cur * (n - num));
                }
                Add(dq[num][num], cur * sz);
                Add(dq[num][sz], cur * (num - sz));
            }
        }
        swap(dp, dq);
    }
    cout << dp[n][n] << '\n';
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