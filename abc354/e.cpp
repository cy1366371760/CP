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
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    vector<vector<int>> can(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            can[i][j] = (a[i] == a[j] || b[i] == b[j]);
        }
    }
    int lim = (1 << n) - 1;
    vector<int> dp(lim + 5, 0);
    for (int s = 0; s <= lim; s++) {
        for (int i = 0; i < n; i++) {
            if (s >> i & 1) {
                for (int j = 0; j < n; j++) {
                    if (can[i][j] && (s >> j & 1)) {
                        dp[s] |= (dp[s ^ (1 << i) ^ (1 << j)] ^ 1);
                    }
                }
            }
        }
    } 
    cout << (dp[lim] == 0 ? "Aoki" : "Takahashi") << '\n';
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
