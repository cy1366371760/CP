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
const int N = 55;
const ll inf = 1e18;
const ll mod = 1e9 + 7;

ll dp[N][2 * N * N], dq[N][2 * N * N];

void Add(ll &x, ll y) {
    x = (x + y) % mod;
}

void solve() {
    int n, k;
    cin >> n >> k;
    dp[0][0] = 1;
    for (int val = n; val >= 1; val--) {
        memset(dq, 0, sizeof dq);
        for (int el = 0; el <= n - val; el++) {
            if (el > val) break;
            int ps = el;
            {
                if (ps > val) break;
                int lim = (n + val + 1) * (n - val);
                for (int sum = 0; sum <= lim; sum++) {
                    // new ele on new ps
                    ll nw = dp[ps][sum];
                    if (!nw) continue;
                    Add(dq[ps][sum], nw);
                    // No use new ele & No use new ps
                    Add(dq[ps + 1][sum + 2 * val], nw);
                    // No use new ele & use new ps
                    if (el) {
                        Add(dq[ps][sum], nw * el % mod);
                    }
                    // use new ele & No use new ps
                    if (ps) {
                        Add(dq[ps][sum], nw * ps % mod);
                    }
                    // use new ele & use new ps
                    if (el && ps && sum >= 2 * val) {
                        Add(dq[ps - 1][sum - 2 * val], nw * el % mod * ps % mod);
                    }
                }
            }
        }
        memcpy(dp, dq, sizeof dp);

    }
    cout << dp[0][k] << '\n';
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