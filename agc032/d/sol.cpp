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
    int n;
    ll A, B;
    cin >> n >> A >> B;
    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector<ll> dp(n + 1, inf);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        vector<ll> dq(n + 1, inf);
        for (int j = 0; j < i; j++) {
            if (p[i] > p[j]) {
                chkmin(dq[i], dp[j]);
                chkmin(dq[j], dp[j] + A);
            } else {
                chkmin(dq[j], dp[j] + B);
            }
        }
        swap(dp, dq);
    }
    cout << *min_element(all(dp)) << '\n';
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