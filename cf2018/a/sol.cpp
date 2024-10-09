#include<bits/stdc++.h>

#define nl '\n'
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
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(all(a));
    ll las = k;
    ll tot = accumulate(all(a), k);
    for (int i = 0; i < n - 1; i++) {
        ll add = min(las, a[n - 1] - a[i]);
        las -= add;
        a[i] += add;
    }
    sort(all(a));
    ll mx = a[n - 1];
    if (las) {
        cout << n << nl;
        return;
    }
    ll may = tot / mx;
    ll res = 1;
    for (ll i = 2; i <= may; i++) {
        ll go = (tot / i) * i;
        if (go >= tot - k && go <= tot) {
            res = i;
        }
    }
    cout << res << nl;
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