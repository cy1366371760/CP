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
    ll n, k, qq;
    cin >> n >> k >> qq;
    ll nw = 1;
    vector<ll> lr;
    lr.pb(1);
    for (int i = 1; ; i++) {
        nw = nw + (nw + k - 1) / k;
        lr.pb(nw);
        if (nw >= n) {
            // cerr << i << ' ' << nw << nl;
            break;
        }
    }
    vector<ll> rl;
    nw = n;
    rl.pb(n);
    for (int i = 1; ;i++) {
        ll lb = 1, rb = nw - 1, mid, res = nw - 1;
        while (lb <= rb) {
            mid = (lb + rb) >> 1;
            ll to = mid + (mid + k - 1) / k;
            if (to >= nw) {
                res = mid;
                rb = mid - 1;
            } else lb = mid + 1;
        }
        nw = res;
        rl.pb(nw);
        if (nw <= 1) {
            break;
        }
    }
    while (qq--) {
        ll x;
        cin >> x;
        ll res = lower_bound(all(lr), x) - lr.begin();
        res += lower_bound(all(rl), x, greater<ll>()) - rl.begin();
        cout << res << nl;
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