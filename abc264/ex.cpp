#include<bits/stdc++.h>
#define ll long long
#define nl '\n'
#define all(x) (x).begin(),(x).end()
using namespace std;
const ll mod = 998244353;

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}

void Sub(ll &x, ll y) {
    x = (x - y % mod + mod) % mod;
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
    int n;
    cin >> n;
    vector<int> fa(n + 5, 0);
    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
    }
    vector dp(25, vector<ll>(n + 5, 0));
    vector sum(2, vector(25, vector<ll>(n + 5, 0)));
    ll inv2 = qpow(2);
    auto add = [&](int x) {
        int dep = 1;
        int son = -1; 
        ll bf_val = -1;
        for (int i = 0; i < 20 && x; i++) {
            if (dep == 1) {
                bf_val = dp[1][x];
                dp[1][x]++;
            } else {
                Sub(sum[0][dep][x], bf_val);
                Sub(sum[1][dep][x], bf_val * bf_val % mod);
                Add(sum[0][dep][x], dp[dep - 1][son]);
                Add(sum[1][dep][x], dp[dep - 1][son] * dp[dep - 1][son] % mod);
                bf_val = dp[dep][x];
                dp[dep][x] = (sum[0][dep][x] * sum[0][dep][x] % mod - sum[1][dep][x] + mod) % mod * inv2 % mod; 
            }
            son = x;
            x = fa[x];
            ++dep;
        }
    };
    for (int i = 1; i <= n; i++) {
        add(i);
        ll res = 0;
        for (int j = 0; j < 20; j++) {
            Add(res, dp[j][1]);
        }
        cout << res << nl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}