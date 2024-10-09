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

map<pll, ll> vis;

int n, k;
ll ask(ll l, ll x) {
    if (l > n || l < 1) return n + 1;
    if (vis.count(pll(l, x))) return vis[pll(l, x)];
    cout << "? " << l << ' ' << x << endl;
    cout.flush();
    ll res;
    cin >> res;
    return vis[pll(l, x)] = res;
}

ll answer(ll x) {
    cout << "! " << x << endl;
    cout.flush();
    ll re;
    cin >> re;
    if (re == -1) exit(0);
    assert(re == 1);
    return re;
}

void solve() {
    vis.clear();
    ll mx = 1;
    cin >> n >> k;
    vector<ll> a(n + 5);
    for (int i = 1; i <= n; i++) {
        ll tmp = ask(1, mx * i);
        while (tmp != i) {
            mx++;
            tmp = ask(1, mx * i);
        }
        a[i] = mx;
        ll cur = 1LL * a[i] * i;
        int ps = i + 1;
        bool flg = 1;
        for (int j = 2; j <= k; j++) {
            ll r = ask(ps, cur);
            if (r == n + 1) {
                flg = 0;
                break;
            }
            vis[pll(1, cur * j)] = r;
            ps = r + 1;
        }
        if (ps == n + 1 && flg) {
            m = max(m, cur);
        }
    }
    vector<ll> may;
    for (int i = 1; i <= n; i++) {
        may.pb(1LL * a[i] * i);
        
    }
    ll m = -1;
    for (int i = 1; i <= n; i++) {
        ll cur = a[i];
        int ps = i + 1;
        bool flg = 1;
        for (int j = 2; j <= k; j++) {
            ll r = ask(ps, cur);
            if (r == n + 1) {
                flg = 0;
                break;
            }
            vis[pll(1, cur * j)] = r;
            ps = r + 1;
        }
        if (ps == n + 1 && flg) {
            m = max(m, cur);
            break;
        }
    }
    answer(m);
}

signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--)
        solve();
    return 0;
}
