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
    vector<array<int, 3>> a(n);
    for (int i = 0; i < n; i++) {
        int aa, cc;
        cin >> aa >> cc;
        a[i] = {cc, aa, i};
    }
    sort(all(a));
    int mx = -1e9;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (a[i][1] < mx) continue;
        mx = a[i][1];
        ans.pb(a[i][2]);
    }
    sort(all(ans));
    cout << ans.size() << '\n';
    for (auto v : ans) cout << v + 1 << ' ';
    cout << '\n';
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
