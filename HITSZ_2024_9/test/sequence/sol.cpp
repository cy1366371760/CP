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
    vector<ll> a(n + 5);
    vector<int> rdif(n + 5), ldif(n + 5);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ldif[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (a[i] == a[i - 1]) ldif[i] = ldif[i - 1];
        else ldif[i] = i - 1;
    }
    rdif[n] = n + 1;
    for (int i = n - 1; i >= 1; i--) {
        if (a[i] == a[i + 1]) rdif[i] = rdif[i + 1];
        else rdif[i] = i + 1;
    }
    int r = n;
    ll cur = 0;
    auto append_l = [&](int l, int r) {
        int sam = rdif[l] - 1;
        ll nw = min(sam, r) - l + 1;
        cur -= (nw - 1) * (nw - 1) * a[l];
        cur += nw * nw * a[l];
    };
    auto del_r = [&](int l, int r) {
        int sam = ldif[r] + 1;
        ll nw = r - max(l, sam) + 1;
        cur -= nw * nw * a[r];
        cur += (nw - 1) * (nw - 1) * a[r];
    };
    ll ans = 0;
    for (int l = n; l >= 1; l--) {  
        append_l(l, r);
        while (cur > k) del_r(l, r), --r;
        if (cur == k && l <= r) {
            if (a[r] == 0) {
                int ok = ldif[r];
                ans += r - max(ok, l) + 1;
            } else {
                ans += 1;
            }
        }
    }
    cout << ans << nl;
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