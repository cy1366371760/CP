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
    ll n, c;
    cin >> n >> c;
    vector<ll> a(n * 2 + 5);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = n; i < 2 * n; i++) {
        a[i] = a[i - n];
    }
    auto sum = a;
    for (int i = 1; i < sum.size(); i++) {
        sum[i] += sum[i - 1];
    }
    vector<vector<ll>> jp(21, vector<ll> (n * 2 + 5));
    for (int i = sum.size() - 1; i >= 0; i--) {
        ll need = c;
        if (i > 0) need += sum[i - 1];
        int to = lower_bound(all(sum), need) - sum.begin();
        jp[0][i] = to;
        // cerr << "??" << i << ' ' << jp[0][i] << '\n';
    }
    for (int j = 1; j <= 20; j++) {
        for (int i = 0; i < sum.size(); i++) {
            if (jp[j - 1][i] + 1 >= sum.size()) {
                jp[j][i] = sum.size();
            } else {
                jp[j][i] = jp[j - 1][jp[j - 1][i] + 1];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int bound = i + n - 1;
        int ans = 0;
        int nw = i;
        for (int j = 20; j >= 0; j--) {
            if (nw < sum.size() && jp[j][nw] < bound) {
                // if (i == 1) {
                //     cerr << "!!" << j << ' ' << nw << ' ' << jp[j][nw] << '\n';
                // }
                ans += 1 << j;
                nw = jp[j][nw] + 1;
            }
        }
        cout << ans << ' ';
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