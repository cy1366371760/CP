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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> ans;
    vector<bool> vis(n, 0);
    for (int step = 0; step < n; step++) {
        bool flg = 0;
        for (int i = 0; i < n; i++) {
            if (vis[i]) {
                continue;
            }
            ll nw = a[i];
            ll divided = 1;
            for (int j = 0; j < n; j++) {
                if (vis[j] || j == i) continue;
                ll cur = a[j];
                cur /= __gcd(divided, cur);
                cur = __gcd(nw, cur);
                divided *= cur;
                nw /= cur;
            }
            if (nw > 1 || step == n - 1) {
                ans.pb(a[i]);
                flg = 1;
                vis[i] = 1;
                break;
            }
        }
        if (!flg) {
            cout << "No" << '\n';
            return;
        }
    }
    reverse(all(ans));
    cout << "Yes" << '\n';
    for (auto x : ans) cout << x << ' ' ;
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