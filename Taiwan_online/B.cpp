#include<bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(),(x).end()
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 5, 0);
    vector<ll> sum(n + 5, 0);
    vector<ll> abs_sum(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
        abs_sum[i] = abs_sum[i - 1] + abs(a[i]);
    }
    ll best_l = 0, ans = abs_sum[n];
    for (int i = 1; i <= n; i++) {
        ll nw = abs_sum[n] - abs_sum[i] + 2 * sum[i] + best_l;
        ans = max(ans, nw);
        best_l = max(best_l, abs_sum[i] - 2 * sum[i]);
    }
    cout << ans << nl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}