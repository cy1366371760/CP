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
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    ll ht = d - b;
    ll val[4];
    if (abs(b) & 1) {
        if (d & 1) {
            val[0] = ht / 2 * 3;
            val[1] = ht / 2 * 3;
            val[2] = ht / 2;
            val[3] = ht / 2;
        } else {
            val[0] = 1 + (ht / 2) * 3;
            val[1] = 2 + (ht / 2) * 3;
            val[2] = 1 + ht / 2;
            val[3] = ht / 2;
        }
    } else {
        if (d & 1) {
            val[0] = 2 + (ht / 2) * 3;
            val[1] = 1 + (ht / 2) * 3;
            val[2] = ht / 2;
            val[3] = 1 + ht / 2;
        } else {
            val[0] = ht / 2 * 3;
            val[1] = ht / 2 * 3;
            val[2] = ht / 2;
            val[3] = ht / 2;
        }
    }
    auto type = [&](ll v) {
        v = (v % 4 + 4) % 4;
        return v;
    };
    ll cnt[4] = {0};
    while ((c - a) % 4) {
        ++cnt[type(a)];
        a++;
    }
    ll ans = 0;
    for (int i = 0; i < 4; i++) cnt[i] += (c - a) / 4, ans += cnt[i] * val[i];
    cout << ans << '\n';
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
