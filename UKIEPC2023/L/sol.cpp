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
    int h[3], d[3], t[3];
    for (int i = 1; i <= 2; i++) {
        cin >> h[i] >> d[i] >> t[i];
    }
    auto calc = [&](int blood, int damage, int reload) {
        int res = blood / damage + (blood % damage ? 1 : 0);
        return (res - 1) * reload;
    };
    int fir, sec;
    fir = calc(h[2], d[1], t[1]);
    sec = calc(h[1], d[2], t[2]);
    if (fir < sec) {
        cout << "player one" << '\n';
    } else if (fir > sec) {
        cout << "player two" << '\n';
    } else {
        cout << "draw" << '\n';
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