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
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(all(a));
    vector<int> cnt;
    for (int i = 0; i < n; i++) {
        int j = i;
        while(j < n && a[j] == a[i])
            j++;
        cnt.pb(j - i);
        i = j - 1;
    }
    vector<int> dp(n + 5, (int)1e9);
    dp[0] = 0;
    for (int i = 0; i < cnt.size(); i++) {
        int nw = cnt[i];
        vector<int> dq(n + 5, (int)1e9);
        for (int d = 0; d <= i; d++) {
            chkmin(dq[d + 1], dp[d] + 1);
            if (nw <= d) {
                chkmin(dq[d - nw], dp[d]);
            }
        }
        dp = dq;
    }
    cout << *min_element(all(dp)) << '\n';
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
