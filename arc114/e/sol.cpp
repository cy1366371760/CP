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

ll qpow(ll x, ll y = mod - 2) {
    ll res = 1;
    while (y) {
        if (y & 1) {
            res = res * x % mod;
        }
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

void solve() {
    ll H, W;
    ll h1, w1, h2, w2;
    cin >> H >> W;
    cin >> h1 >> w1 >> h2 >> w2;
    vector<ll> inv(H + W + 5, 0), sinv(H + W + 5, 0);
    for (int i = 1; i < inv.size(); i++) {
        inv[i] = qpow(i);
        sinv[i] = (sinv[i - 1] + inv[i]) % mod;
    }
    if (h1 > h2) swap(h1, h2);
    if (w1 > w2) swap(w1, w2);
    array<ll, 4> vals;
    ll mid;
    vals[0] = h1 - 1;
    vals[1] = H - h2;
    vals[2] = w1 - 1;
    vals[3] = W - w2;
    mid = h2 - h1 + w2 - w1;
    ll res = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= vals[i]; j++) {
            res = (res + inv[j + mid]) % mod;
        }
    }
    cout << (res + 1) % mod;
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