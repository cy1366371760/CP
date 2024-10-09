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
const int N = 110;
const ll inf = 1e18;
const ll mod = 998244353;

int dp[N][N][N];

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 5);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    memset(dp, 0, sizeof dp);
    auto ask = [&](int ps, int val) {
        if (ps < val) return -1;
        int need = ps - val;
        if (need & 1) return -1;
        return need / 2;
    };
    for (int le = 2; le <= n; le++) {
        for (int l = 1; l + le - 1 <= n; l++) {
            int r = l + le - 1;
            for (int lim = 0; lim <= n; lim++) {
                chkmax(dp[l][r][lim], dp[l + 1][r][lim]);
                chkmax(dp[l][r][lim], dp[l][r - 1][lim]);
                if (le == 2) {
                    int need = ask(l, a[l]);
                    if (need >= 0) {
                        dp[l][r][need] = 1;
                    }
                }
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}
