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

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}

ll qpow(ll x, ll y = mod - 2) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> p(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector dp(3, vector<ll>(3, 0));
    dp[1][2] = 1;
    auto C2 = [&](ll x) {
        return (x * (x - 1) / 2LL) % mod;
    };
    for (int i = 1; i <= m; i++) {
        vector dq(3, vector<ll>(3, 0));
        for (int fir = 0; fir <= 2; fir++) {
            for (int sec = 0; sec <= 2; sec++) {
                if (fir != 0 && fir == sec) continue;
                ll nw = dp[fir][sec];
                // no change
                Add(dq[fir][sec], C2(n - 2) * nw);
                // swap fir & sec
                Add(dq[sec][fir], nw);
                // change fir with outside
                ll out_other = n - 2 - (fir == 0) - (sec == 0);
                for (int out = 0; out <= 2; out++) {
                    if (out && (out == fir || out == sec)) continue;
                    if (out == 0) {
                        Add(dq[0][sec], nw * out_other);
                        Add(dq[fir][0], nw * out_other);
                    } else {
                        Add(dq[out][sec], nw);
                        Add(dq[fir][out], nw);
                    }
                }
            }
        }
        swap(dp, dq);
    }
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         cerr << "!!" << i << ' ' << j << ' ' << dp[i][j] << '\n';
    //     }
    // }
    ll inv1 = qpow(n - 2);
    ll inv2 = qpow(C2(n - 2));
    ll res = 0;

    auto calc_sum = [&](ll l, ll r) {
        return ((l + r) * (r - l + 1) / 2LL) % mod;
    };
    ll all = 0;
    for (int i = 2; i <= n; i++) {
        Add(all, 1LL * i * (i - 1) - calc_sum(1, i - 1));
    }
    for (int i = 1; i < n; i++) {
        Add(res, abs(p[i + 1] - p[i]) * (dp[1][2] + dp[2][1]) % mod);
        ll v_fir = (p[i] * (p[i] - 1) % mod - calc_sum(1, p[i] - 1) + mod) % mod + 
                   (calc_sum(p[i] + 1, n) - p[i] * (n - p[i]) + mod) % mod;
        ll v_sec = (p[i + 1] * (p[i + 1] - 1) % mod - calc_sum(1, p[i + 1] - 1) + mod) % mod + 
                   (calc_sum(p[i + 1] + 1, n) - p[i + 1] * (n - p[i + 1]) + mod) % mod;
        v_fir = (v_fir - abs(p[i + 1] - p[i]) + mod) % mod;
        v_sec = (v_sec - abs(p[i + 1] - p[i]) + mod) % mod;
        Add(res, v_fir * (dp[0][1] + dp[1][0]) % mod * inv1);
        Add(res, v_sec * (dp[0][2] + dp[2][0]) % mod * inv1);
        ll v_other = ((all - v_fir - v_sec - abs(p[i] - p[i + 1])) % mod + mod) % mod;
        Add(res, v_other * dp[0][0] % mod * inv2);
        // cerr << "!!" << i << ' ' << all << ' ' << v_fir << ' ' << v_sec << ' ' <<v_other << '\n';
        // cerr << dp[0][1] << ' ' << dp[1][0] << ' ' << n - 2 << '\n';
        // cerr << dp[0][2] << ' ' << dp[2][0] << ' ' << n - 2 << '\n';
    }
    cout << res << '\n';
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