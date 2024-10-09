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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector jp(20, vector<int>(n - 1, 0));
    for (int i = 0; i < n - 1; i++) {
        jp[0][i] = abs(a[i] - a[i + 1]);
    }
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i < n - 1; i++) {
            if (i + (1 << (j - 1)) >= n - 1) {
                jp[j][i] = 1;
                continue;
            }
            jp[j][i] = __gcd(jp[j - 1][i], jp[j - 1][i + (1 << (j - 1))]);
        }
    }
    ll ans = 0;
    auto ask = [&](int l, int r) {
        int d = r - l;
        int res = 0;
        for (int j = 19; j >= 0; j--) {
            if (d >> j & 1) {
                res = __gcd(res, jp[j][l]);
                l += (1 << j);
            }
        }
        return res;
    };
    auto bad = [&](int val) {
        while (val > 0 && val % 2 == 0) {
            val /= 2;
        }
        if (val > 1) return true;
        return false;
    };
    vector<int> dp(n);
    for (int l = n - 1; l >= 0; l--) {
        int lb = l + 1, rb = n - 1, res = n, mid;
        if (l < n - 1 && a[l] == a[l + 1]) {
            dp[l] = dp[l + 1] + 1;
            ans += dp[l];
        } else {
            while (lb <= rb) {
                mid = (lb + rb) / 2;
                int val = ask(l, mid);
                if (bad(val)) {
                    lb = mid + 1;
                } else {
                    res = mid;
                    rb = mid - 1;
                }
            }
            dp[l] = n - res + 1;
            ans += dp[l];
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