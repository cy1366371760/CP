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

void solve() {
    int n;
    cin >> n;
    vector<int> R(n, 0), C(n, 0);
    for (int i = 0; i < n; i++) cin >> R[i];
    for (int i = 0; i < n; i++) cin >> C[i];
    int num[3] = {0};
    for (int i = 0; i < n; i++) num[R[i]]++;
    vector<ll> dp(num[2] + 5, 0);
    dp[num[2]] = 1;
    int tot_use = 0;
    auto C2 = [&](ll x) {
        return x * (x - 1) / 2LL % mod;
    };
    for (int i = 0; i < n; i++) {
        int nw = C[i];
        if (nw == 0) continue;
        vector<ll> dq(num[2] + 5, 0);
        for (int two = 0; two <= num[2]; two++) {
            ll one = num[1] + num[2] * 2 - tot_use - two * 2;
            if (one < 0 || dp[two] == 0) continue;
            if (nw == 1) {
                // use one
                if (one) {
                    Add(dq[two], dp[two] * one);
                }
                // use two
                if (two) {
                    Add(dq[two - 1], dp[two] * two);
                }
            } else {
                // use one * 2
                if (one >= 2) {
                    Add(dq[two], dp[two] * C2(one));
                }
                // use two * 1
                if (two) {
                    Add(dq[two - 1], dp[two] * two);
                }
                // use two * 2
                if (two >= 2) {
                    Add(dq[two - 2], dp[two] * C2(two));
                }
                // one + two
                if (one && two) {
                    Add(dq[two - 1], dp[two] * one % mod * two);
                }
            }
        }
        swap(dp, dq);
        tot_use += nw;
    }
    ll one = num[1] + num[2] * 2 - tot_use;
    if (one) {
        cout << 0 << '\n';
    } else {
        cout << dp[0] << '\n';
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