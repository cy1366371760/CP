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
    int n, m;
    cin >> n >> m;
    if (n == 1 && m == 1) {
        cout << 1 << nl << 1 << nl;
        return;
    }
    if (m == 1 || m == n) {
        cout << -1 << nl;
        return;
    }
    if (m % 2 == 0) {
        cout << 3 << nl;
        cout << 1 << ' ' << m << ' ' << m + 1 << nl;
    } else {
        cout << 5 << nl;
        cout << 1 << ' ' << 2 << ' ' << m << ' ' << m + 1 << ' ' << m + 2 << nl;
    }
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