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
#define int long long

void solve() {
    int n, m;
    cin >> n >> m;
    ll each = 0;
    for (int i = 1; i <= n; i++) {
        int len;
        cin >> len;
        vector<bool> vis(len + 5, 0);
        for (int j = 1; j <= len; j++) {
            int x;
            cin >> x;
            if (x <= len + 2) {
                vis[x] = 1;
            }
        }
        ll A, B;
        bool skip = 0;
        for (int j = 0; j <= len + 3; j++) {
            if (!vis[j]) {
                if (skip) {
                    B = j;
                    break;
                }
                A = j;
                skip = 1;
            }
        }
        chkmax(each, B);
    }
    ll ans = 0;
    if (m < each) {
        ans = each * (m + 1);
    } else {
        ans += m * (m + 1) / 2LL;
        ans += each * (each + 1) / 2LL;
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