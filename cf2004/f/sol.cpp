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
    vector<int> a(n), pre(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + a[i];
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ans += j - i + 1;
        }
    }
    map<int, int> cnt;
    cerr << ans << '\n';
    for (int len = n; len >= 1; len--) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            ++cnt[pre[i - 1] + pre[j]];
            // cerr << "Add: " << i << ' ' << j << ' ' << pre[i] + pre[j - 1] << '\n';
        }
        for (int ii = 1; ii <= n; ii++) {
            int jj = ii - len + 1;
            if (jj >= 1) {
                ans -= cnt[pre[ii] + pre[jj - 1]];
                // cerr << "Ask: " << ii << ' ' << jj << ' ' << pre[ii] + pre[jj - 1] << ' ' << cnt[pre[ii] + pre[jj - 1]] << '\n';
            }
            jj = ii + len - 1;
            if (len != 1 && jj <= n) {
                ans -= cnt[pre[ii] + pre[jj - 1]];
                // cerr << "Ask: " << ii << ' ' << jj << ' ' << pre[ii] + pre[jj - 1] << ' ' << cnt[pre[ii] + pre[jj - 1]] << '\n';
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