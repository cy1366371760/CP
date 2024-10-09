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
    vector<ll> a(n, 0);
    for(ll &i : a)
        cin >> i;
    vector<ll> sum(n);
    sum[0] = a[0];
    ll mn = min(0LL, a[0]);
    for(int i = 1; i < n; i++)
        sum[i] = sum[i - 1] + a[i], chkmin(mn, sum[i]);
    ll ans = 0;
    vector<ll> prev(n, 0);
    ll tmp = 1, ss = 0;
    for (int i = 0; i < n; i++) {
        ll need = ss + a[i];
        if (abs(ss + a[i]) == need) {
            tmp *= 2;
            tmp %= mod;
        }
        ss = need;
        prev[i] = tmp;
        // cerr << i << ' ' << prev[i] << '\n';
    }
    vector<ll> pw2(n + 5, 1);
    for (int i = 1; i <= n; i++) {
        pw2[i] = pw2[i - 1] * 2LL % mod;
    }
    if (mn >= 0) {
        cout << pw2[n] << '\n';
        return;
    }
    for (int i = 0; i < n; i++) {
        if (sum[i] == mn) {
            ans += prev[i] * pw2[n - 1 - i];
            ans %= mod;
        }
    }
    if (mn == 0LL) {
        ans = (ans + pw2[n]) % mod;
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
