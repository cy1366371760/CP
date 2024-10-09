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
    ll p1, p2, p3;
    cin >> p1 >> p2 >> p3;
    int mx = -1;
    for (int d12 = 0; d12 <= p1; d12++) {
        for (int d13 = 0; d13 <= p1; d13++) {
            for (int d23 = 0; d23 <= p2; d23++) {
                if ((p1 - d12 - d13) >= 0 && (p1 - d12 - d13) % 2 == 0) {
                    if ((p2 - d12 - d23) >= 0 && (p2 - d12 - d23) % 2 == 0) {
                        if ((p3 - d13 - d23) >= 0 && (p3 - d13 - d23) % 2 == 0) {
                            mx = max(mx, d12 + d13 + d23);
                        }
                    }
                }
            }
        }
    }
    cout << mx << '\n';
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
