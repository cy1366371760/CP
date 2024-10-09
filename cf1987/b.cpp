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
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> need;
    ll mx = -1;
    for (int i = 0; i < n; i++) {
        chkmax(mx, a[i]);
        if (a[i] < mx)
            need.pb(mx - a[i]);
    }
    sort(all(need));
    ll res = 0;
    for (int i = 0; i < need.size(); i++) {
        ll nw;
        if (i == 0) nw = need[i];
        else nw = need[i] - need[i - 1];
        res += 1LL * nw * (need.size() - i + 1);
    }
    cout << res << '\n';
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
