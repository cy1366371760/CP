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
    vector<int> pre(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> LIS;
    for (int i = 0; i < n; i++) {
        int ps = lower_bound(all(LIS), a[i]) - LIS.begin();
        if (ps == LIS.size()) {
            LIS.pb(a[i]);
        } else LIS[ps] = a[i];
        pre[i] = ps;
        // cerr << ps << ' ';
    }
    int mx_len = LIS.size();
    LIS.clear();
    vector<int> ans;
    for (int i = n - 1; i >= 0; i--) {
        int ps = lower_bound(all(LIS), a[i], greater<int>()) - LIS.begin();
        if (ps == LIS.size()) {
            LIS.pb(a[i]);
        } else LIS[ps] = a[i];
        if (ps + pre[i] + 1 == mx_len) {
            ans.pb(i + 1);
        }
    }
    sort(all(ans));
    cout << ans.size() << '\n';
    for (int v : ans) cout << v << ' ';
    cout << '\n';
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
