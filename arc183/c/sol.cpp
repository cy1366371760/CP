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
const int N = 550;
const ll inf = 1e18;
const ll mod = 998244353;

vector<pii> ban[N];

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}

ll C[N][N];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        ban[l].pb({r, x});
    }
    vector<int> mnr(510, n + 5);
    vector dp(n + 5, vector<ll>(n + 5, 0));
    for (int i = 0; i <= n; i++) {
        dp[i + 1][i] = 1;
    }
    for (int l = n; l >= 1; l--) {
        for (auto [r, x] : ban[l]) {
            chkmin(mnr[x], r);
        }
        for (int r = l; r <= n; r++) {
            ll cur = 0;
            for (int mx = l; mx <= r; mx++) {
                if (mnr[mx] > r) {
                    Add(cur, dp[l][mx - 1] * dp[mx + 1][r] % mod * C[r - l][mx - 1 - l + 1]);
                }
            }
            dp[l][r] = cur;
        }
    }
    cout << dp[1][n] << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // int tt = 1;
    // cin >> tt;
    // while(tt--)
    int n = 505;
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
    }
    solve();
    return 0;
}