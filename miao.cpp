#include<bits/stdc++.h>

#define ll long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define eb emplace_back
#define fi first
#define sc second
#define nl '\n'
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
    cerr << sizeof (long double) << nl;
    cerr << sizeof (double) << nl;
    cerr << sizeof (__float128) << nl;
    int n = 32;
    int m = 8;
    int w = 80;
    for (int i = 0; i < n; i += m) {
        for (int j = 0; j < n; j += m) {
            cout << '[' << i + m / 2 << ',' << j + m / 2 << ',' << w << ']' << ',';
            cout << '[' << i + m - 1 << ',' << j + m - 1 << ',' << w << ']' << ',';
        }
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
