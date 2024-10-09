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
    ll m;
    cin >> n >> m;
    vector<ll> a(n * 2 - 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i + 1 < n) {
            a[i + n] = a[i];
        }
    }
    vector<ll> pref(n * 2);
    map<ll,ll> cnt;
    ll ans = 0;
    for (int i = 0; i < n * 2; i++) {
        if (i + 1 < n * 2) {
            pref[i + 1] = (pref[i] + a[i]) % m;
        }
    }
    // for (int i = 0; i < n * 2; i++) {
    //     cerr << pref[i] << ' ';
    // }
    // cerr << '\n';
    for (int i = 0; i < n * 2; i++) {
        if (i >= n) --cnt[pref[i - n]];
        ans += cnt[pref[i]];
        // cerr << i << ' ' << cnt[pref[i]] << '\n';
        if (i < n) cnt[pref[i]]++;
    }
    cout << ans << '\n';
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