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
    ll n, l, r, p;
    cin >> n >> l >> r >> p;
    ll g = 0;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        g = __gcd(g, x);
    }
    int lhs = 0, rhs = 0;
    while (p + (lhs - 1) * g >= l) --lhs;
    while (p + (rhs + 1) * g <= r) ++rhs;
    cout << rhs - lhs + 1 << nl;
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