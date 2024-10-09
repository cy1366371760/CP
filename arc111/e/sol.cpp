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

ll floor_sum(ll a, ll b, ll c, ll n) { // sum i=0...n, floor((a*i + b)/c)
    if (a == 0) {  
        return (n + 1) * (b / c) ;  
    }  
    ll mx = (a * n + b) / c; // 0, mx - 1  
    if (mx == 0) {  
        return 0;  
    }  
    if (a >= c || b >= c) {  
        return (n * (n + 1) / 2 * (a / c)  + (n + 1) * (b / c) + floor_sum(a % c, b % c, c, n));  
    }  
    return (mx * (n + 1) - floor_sum(c, a + c - b - 1, a, mx - 1));
}

void solve() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    ll lim = (d - 2) / (c - b);
    ll res = lim - (floor_sum(c, a, d, lim) - floor_sum(b, a - 1, d, lim));
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