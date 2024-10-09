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
const int N = 1e9 + 100;
const ll inf = 1e18;
const ll mod = 998244353;

bool vis[N];

void solve() {
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        ++ans;
        int v2 = is_vis(1LL * i * 2), v3 = is_vis(1LL * i * 3);
        if (v2 + v3 <= 1 || (i & 1)) {
            if (!v2) vis[i * 2] = 1;
            if (!v3) vis[i * 3] = 1;
        } else {
            if (!is_vis(1LL * i / 2 * 3)) {
                vis[1LL * i / 2 * 3] = 1;
            }
        }
    }
    cout << ans << nl;
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