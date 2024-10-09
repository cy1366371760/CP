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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> las(m + 1, 0);
    vector<int> ans(m + 1, 0);
    while (k--) {
        int p, c;
        cin >> p >> c;
        if (las[c] != 0) {
            ans[c] += (las[c] == p ? 100: abs(las[c] - p));
            las[c] = 0;
        } else las[c] = p;
    }
    for (int i = 1; i <= m; i++) {
        if (las[i]) ans[i] += 100;
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