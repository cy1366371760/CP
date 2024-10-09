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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ld ans = 0;
    auto calc = [&](vector<int> cur) {
        vector<ld> d;
        for (int i = 0; i + 1 < cur.size(); i++) {
            d.pb(cur[i + 1] - cur[i]);
        }
        sort(all(d));
        int num = d.size();
        ld res = 0;
        for (int i = 0; i < num; i++) {
            res += d[i] * (i + 1);
        }
        res /= (ld)(num * (num + 1));
        return res;
    };
    for (int cas = 0; cas < (1 << n); cas++) {
        vector<int> cur;
        for (int i = 0; i < n; i++) {
            if (cas & (1 << i)) {
                cur.pb(a[i]);
            }
        }
        if (cur.size() < k) {
            continue;
        }
        ans = max(ans, calc(cur));
    }
    cout << fixed << setprecision(10) << ans << '\n';
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
