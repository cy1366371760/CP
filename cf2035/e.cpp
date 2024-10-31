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
    ll add, dam, n, wait;
    cin >> add >> dam >> n >> wait;
    wait = min(wait, n);
    /*
        x = (n + l – 1) / l, r = (x == 1 ? l : (n – 1) / (x – 1))
    */
    ll ans = inf;
    auto ask = [&](ll tim) -> ll {
        ll res = 0;
        ll las = n;
        ll tmp = tim / wait;
        res += tmp * (wait * add + dam);
        las -= wait * (1LL + tmp) * tmp / 2LL;
        res += (tim % wait) * add;
        if (las > 0) {
            res += las / tim * dam;
            if (las % tim) res += dam;
        }
        return res;
    };
    vector<pll> may;
    for (ll p = 0;; p++) {
        ll las = n;
        las -= wait * (1LL + p) * p / 2LL;
        if (las > 0) {
            may.pb(pll(p * wait, las));
        } else if (las == 0) {
            chkmin(ans, ask(wait * p));
        } else break;
    }
    for (auto [extra, n] : may) {
        // cerr << " " << extra << ' ' << n << nl;
        for (ll l = max(1LL, extra), r; l <= extra + wait && l <= n; l = r + 1) {
            ll x = (n + l - 1) / l;
            r = (x == 1 ? l : (n - 1) / (x - 1));
            chkmin(ans, ask(l));
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